using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinVocaloid
{
    public partial class MusicBox : UserControl
    {
        public MusicBox()
        {
            InitializeComponent();
            musics = new LinkedList<MusicNote>();
        }

        LinkedList<MusicNote> musics;

        class MusicNote
        {
            public int Note;
            public float Beat;
        }

        protected override void WndProc(ref Message m)
        {
            base.WndProc(ref m);
            if (m.Msg == 0x0102)
            {
                int num = m.WParam.ToInt32();
                char ch = (char)num;
                Append(ch);
                Draw();
            }
        }

        private void Draw()
        {
            int x = 0, y = 0;
            Controls.Clear();
            foreach (var n in musics)
            {
                var lbl = new Label() { Text = $"{n.Note}/{n.Beat}" };
                lbl.AutoSize = true;
                lbl.Left = x;
                lbl.Top = y;
                Controls.Add(lbl);
                x += lbl.Width;
                if (x + lbl.Width >= Width)
                {
                    x = 0;
                    y += lbl.Height;
                }
            }

            Focus();
        }

        public void Append(int note, float beat = 1.0f)
        {
            musics.AddLast(new MusicNote { Note = note, Beat = beat });
        }
    }
}
