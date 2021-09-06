//
//  VOCALOID Light Synthesis API Sample.
//  main.cpp
//  Version 3.0.0d
//
//  Copyright (c) 2017- Yamaha Corporation. All rights reserved.
//

#include <cstdio>
#include <iostream>
#include <cstdint>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include <string>
#include <limits.h>
#include <unistd.h>

#include <grpc/grpc.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include "protos/server.pb.h"
#include "protos/server.grpc.pb.h"

#include "VLS_wrapper.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using MyVocaloid::Note;
using MyVocaloid::SingRequest;
using MyVocaloid::SingReply;
using MyVocaloid::Vocaloid;

std::string getDirectory(const std::string& str)
{
  size_t found;
  found=str.find_last_of("/\\");
  return str.substr(0,found);
}

std::string getexepath()
{
  char result[ PATH_MAX ];
  ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
  return std::string( result, (count > 0) ? count : 0 );
}

class VocaloidService final : public Vocaloid::Service 
{
    Status Sing(ServerContext* context, const SingRequest* request, SingReply* reply) override 
    {
        int bank = request->bank();
        int bpm = request->bpm();
        std::string lyrics = request->lyrics();
        int notes_size = request->notes_size();
        VLS_Note *vnotes = new VLS_Note[notes_size];
        for (int i = 0; i < request->notes_size(); ++i)
        {
            auto note = request->notes(i);
            vnotes[i].note = note.note();
            vnotes[i].start = note.start();
            vnotes[i].duration = note.duration();
        }
        
        int16_t *data;
        int data_size;
        auto ret = VLS_process(&data, data_size, lyrics.c_str(), vnotes, notes_size, bpm, bank);

        reply->set_result(ret.result);
        reply->set_message(ret.message);
        *reply->mutable_data() = {data, data + data_size};

        delete[] vnotes;
        delete[] data;

        return Status::OK;
    }
};

void RunServer(const std::string& path) 
{
    VLS_start(path.c_str());

    std::string server_address("0.0.0.0:50051");
    VocaloidService service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();

	VLS_stop();
}

int main(int argc, char* argv[])
{
	std::string exepath = getexepath();
    std::string path = getDirectory(exepath);
    RunServer(path);
    return 0;
}
