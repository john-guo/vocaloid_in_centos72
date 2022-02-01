using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Diagnostics;
using Microsoft.International.Converters.PinYinConverter;
using Newtonsoft.Json;
using System.IO;

namespace WinVocaloid
{
    public partial class LyricsBox : UserControl
    {
        public static (string title, float factor)[] Beats =
                {
                    ("0", 0),
                    ("1/8", 0.5f),
                    ("1/4", 1.0f),
                    ("1/2", 2.0f),
                    ("1", 4.0f),
                    ("3/2", 6.0f),
                    ("2", 8.0f),
                    ("3", 12.0f),
                    ("4", 16.0f)
                };

        public const int QuarterNote = 2;

        public LyricsBox()
        {
            InitializeComponent();
            ImeMode = ImeMode.HangulFull;
            Cursor = Cursors.IBeam;
            NoteFont = new Font(FontFamily.GenericMonospace, 12.0f, FontStyle.Regular);
            BeatFont = new Font(FontFamily.GenericMonospace, 6.0f, FontStyle.Regular);
            PinyinFont = new Font(FontFamily.GenericMonospace, 10.0f, FontStyle.Regular);
            Font = new Font(FontFamily.GenericMonospace, 12.0f, FontStyle.Regular);
            SetStyle(ControlStyles.OptimizedDoubleBuffer, true);
            SetStyle(ControlStyles.Selectable, true);
        }

        IntPtr m_hImc;

        public const int WM_IME_SETCONTEXT = 0x0281;
        public const int WM_CHAR = 0x0102;


        [DllImport("Imm32.dll")]
        public static extern IntPtr ImmGetContext(IntPtr hWnd);
        [DllImport("Imm32.dll")]
        public static extern IntPtr ImmAssociateContext(IntPtr hWnd, IntPtr hIMC);

        [DllImport("user32.dll")]
        static extern bool CreateCaret(IntPtr hWnd, IntPtr hBitmap, int nWidth, int nHeight);
        [DllImport("user32.dll")]
        static extern bool ShowCaret(IntPtr hWnd);
        [DllImport("User32.dll")]
        static extern bool HideCaret(IntPtr hWnd);
        [DllImport("User32.dll")]
        static extern bool SetCaretPos(int x, int y);
        [DllImport("User32.dll")]
        static extern bool DestroyCaret();


        public Font PinyinFont { get; set; }
        public Font NoteFont { get; set; }
        public Font BeatFont { get; set; }

        private Timer caretTimer = new Timer();
        private Graphics g;

        public int BPM { get; set; } = 120;

        public class LyricChar : ILyricChar
        {
            public char Char { get; set; }
            public string Pinyin { get; set; }
            public char Note { get; set; }
            public int Beat { get; set; }

            public Lazy<ChineseChar> CChar => new Lazy<ChineseChar>(() => new ChineseChar(Char));
        }

        public interface ILyricChar
        {
            char Char { get; }
            string Pinyin { get; }
            char Note { get; }
            int Beat { get; }
        }

        enum CharPosType
        {
            None = 0,
            Header = 1,
            NewLine = 2,
        }

        class CharPos<T> where T : ILyricChar
        {
            public CharPos()
            { }

            public CharPos(T ch, SizeF charSize, SizeF pinyinSize, SizeF noteSize, SizeF beatSize)
            {
                Type = CharPosType.None;
                Holder = ch;
                if (Holder.Char == 13)
                {
                    Type = CharPosType.NewLine;
                }

                Width = (int)Math.Ceiling(Math.Max(Math.Max(charSize.Width, pinyinSize.Width), noteSize.Width + beatSize.Width));
                Height = (int)Math.Ceiling(charSize.Height + pinyinSize.Height + Math.Max(noteSize.Height, beatSize.Height));

                int x = (int)(Width - (noteSize.Width + beatSize.Width)) / 2;
                int y = 0;

                NoteArea = new Rectangle(x, y, (int)noteSize.Width, (int)noteSize.Height);
                x += NoteArea.Width;
                BeatArea = new Rectangle(x, y, (int)beatSize.Width, (int)beatSize.Height);

                x = (int)(Width - pinyinSize.Width) / 2;
                y += Math.Max(NoteArea.Height, BeatArea.Height);
                PinyinArea = new Rectangle(x, y, (int)pinyinSize.Width, (int)pinyinSize.Height);

                x = (int)(Width - charSize.Width) / 2;
                y += PinyinArea.Height;
                CharArea = new Rectangle(x, y, (int)charSize.Width, (int)charSize.Height);
            }

            public CharPosType Type { get; set; }
            public T Holder { get; set; }

            public int Width { get; set; }
            public int Height { get; set; }

            public int X { get; set; }
            public int Y { get; set; }
            public int Line { get; set; }
            public int Column { get; set; }

            public Rectangle NoteArea { get; set; }
            public Rectangle BeatArea { get; set; }
            public Rectangle PinyinArea { get; set; }
            public Rectangle CharArea { get; set; }

            public Rectangle NoteRect
            {
                get
                {
                    return new Rectangle(X + NoteArea.X, Y + NoteArea.Y, NoteArea.Width, NoteArea.Height);
                }
            }

            public Rectangle BeatRect
            {
                get
                {
                    return new Rectangle(X + BeatArea.X, Y + BeatArea.Y, BeatArea.Width, BeatArea.Height);
                }
            }

            public Rectangle PinyinRect
            {
                get
                {
                    return new Rectangle(X + PinyinArea.X, Y + PinyinArea.Y, PinyinArea.Width, PinyinArea.Height);
                }
            }

            public Rectangle CharRect
            {
                get
                {
                    return new Rectangle(X + CharArea.X, Y + CharArea.Y, CharArea.Width, CharArea.Height);
                }
            }

            public Rectangle Rect
            {
                get
                {
                    return new Rectangle(X, Y, Width, Height);
                }
            }
        }

        interface IRender
        {
            SizeF MeasureString(string str, Font font);
            void DrawString(string str, Font font, Brush brush, int x, int y);
        }


        class GraphicsRender : IRender
        {
            Graphics _g;
            public GraphicsRender(Graphics g)
            {
                _g = g;
            }

            public void DrawString(string str, Font font, Brush brush, int x, int y)
            {
                _g.DrawString(str, font, brush, x, y);
            }

            public SizeF MeasureString(string str, Font font)
            {
                return _g.MeasureString(str, font);
            }
        }    

        class LinesEditor<T> where T : ILyricChar
        {
            private LinkedList<CharPos<T>> _text;
            private LinkedListNode<CharPos<T>> _current;

            private List<List<LinkedListNode<CharPos<T>>>> _lines;

            public List<List<LinkedListNode<CharPos<T>>>> Lines => _lines;
            public int Width { get; private set; }
            public int Height { get; private set; }
            public float LineHeight { get; private set; }
            private int lineSpace;
            private int visualCount;
            private int StartLine { get; set; }
            private Font _charFont;
            private Font _pinyinFont;
            private Font _noteFont;
            private Font _beatFont;
            private IRender _render;

            public LinesEditor(int width, int height, Font charFont, Font pinyinFont, Font noteFont, Font beatFont, IRender render)
            {
                _text = new LinkedList<CharPos<T>>();
                _lines = new List<List<LinkedListNode<CharPos<T>>>>();

                Width = width;
                Height = height;
                LineHeight = charFont.GetHeight() + pinyinFont.GetHeight() + Math.Max(noteFont.GetHeight(), beatFont.GetHeight());
                lineSpace = (int)LineHeight;
                visualCount = Height / lineSpace;
                StartLine = 0;

                _charFont = charFont;
                _pinyinFont = pinyinFont;
                _noteFont = noteFont;
                _beatFont = beatFont;
                _render = render;
            }

            public List<List<LinkedListNode<CharPos<T>>>> VisualLines
            { 
                get
                {
                    var count = Math.Max(0, Math.Min(Lines.Count - StartLine, visualCount));
                    return Lines.GetRange(StartLine, count);
                }
            }

            public void Append(T ch)
            {
                var charSize = _render.MeasureString($"{ch.Char}", _charFont);
                var pinyinSize = _render.MeasureString(string.IsNullOrWhiteSpace(ch.Pinyin)?"a":ch.Pinyin, _pinyinFont);
                var noteSize = _render.MeasureString("C", _noteFont);
                var beatSize = _render.MeasureString("1/8", _beatFont);

                var cp = new CharPos<T>(ch, charSize, pinyinSize, noteSize, beatSize);

                if (_current != null)
                    _current = _text.AddAfter(_current, cp);
                else
                    _current = _text.AddFirst(cp);

                GenLines();

                Scroll(GetPostion().Row);
            }

            private string GetNote(char note)
            {
                return $"{note}";
            }

            private string GetBeat(int beat)
            {
                if (beat == 0)
                    return string.Empty;
                return Beats[beat].title;
            }

            public void Render(IRender render = null)
            {
                var first = VisualLines.FirstOrDefault()?.FirstOrDefault()?.Value;
                if (first == null)
                    return;

                render = render ?? _render;
                foreach (var line in VisualLines)
                {
                    foreach (var n in line)
                    {
                        var c = n.Value;

                        render.DrawString(GetNote(c.Holder.Note), _noteFont, Brushes.Black, c.NoteRect.X, c.NoteRect.Y - first.Y);
                        render.DrawString(GetBeat(c.Holder.Beat), _beatFont, Brushes.Black, c.BeatRect.X, c.BeatRect.Y - first.Y);
                        render.DrawString($"{c.Holder.Pinyin}", _pinyinFont, Brushes.Black, c.PinyinRect.X, c.PinyinRect.Y - first.Y);
                        render.DrawString($"{c.Holder.Char}", _charFont, Brushes.Black, c.CharRect.X, c.CharRect.Y - first.Y);
                    }
                }
            }
            
            private void GenLines()
            {
                _lines.Clear();
                if (_text.Count == 0)
                    return;

                var line = new List<LinkedListNode<CharPos<T>>>();
                Lines.Add(line);
                var n = _text.First;
                float x = 0f;
                float y = 0f;
                int col = 0;
                while (n != null)
                {
                    var c = n.Value;
                    if (c.Type == CharPosType.NewLine)
                    {
                        c.Y = (int)y;
                        c.Column = ++col;

                        c.X = (int)x;
                        c.Line = c.Y / lineSpace;

                        line.Add(n);

                        line = new List<LinkedListNode<CharPos<T>>>();
                        Lines.Add(line);

                        y += lineSpace;
                        x = 0f;
                        col = 0;
                    }
                    else
                    {
                        float w = c.Width;
                        if (x + w > Width)
                        {
                            y += lineSpace;
                            x = 0f;
                            col = 0;

                            line = new List<LinkedListNode<CharPos<T>>>();
                            Lines.Add(line);
                        }

                        c.Y = (int)y;
                        c.Column = ++col;

                        c.X = (int)x;
                        c.Line = c.Y / lineSpace;
                        x += w;

                        line.Add(n);
                    }

                    n = n.Next;
                }

            }

            public void Delete(bool previous = true)
            {
                if (_current == null && !previous)
                {
                    if (_text.Count > 0)
                        _text.RemoveFirst();
                    GenLines();
                    return;
                }
                if (_current == null)
                    return;

                if (previous)
                {
                    var prev = _current;
                    _current = _current.Previous;
                    _text.Remove(prev);
                }
                else
                {
                    if (_current.Next != null)
                        _text.Remove(_current.Next);
                }

                GenLines();
            }
           
            public void OnKeyDown(Keys key)
            {
                switch (key)
                {
                    case Keys.Left:
                        _current = _current?.Previous;
                        Scroll(GetPostion().Row);
                        break;
                    case Keys.Right:
                        if (_current == null)
                            _current = _text.First;
                        else if (_current?.Next != null)
                            _current = _current.Next;
                        Scroll(GetPostion().Row);
                        break;
                    case Keys.Up:
                        {
                            var p = GetPostion();
                            int row = p.Row;
                            int col = p.Column;
                            if (row > 0)
                            {
                                int count = _lines[row - 1].Count;
                                if (col == - 1)
                                {
                                    if (row - 2 >= 0)
                                        _current = _lines[row - 2].LastOrDefault();
                                    else
                                        _current = null;
                                }
                                else
                                {
                                    if (count == 0)
                                    {
                                        if (row - 2 >= 0)
                                            _current = _lines[row - 2].LastOrDefault();
                                        else
                                            _current = null;
                                    }
                                    else
                                    {
                                        _current = _lines[row - 1][Math.Max(0, Math.Min(col - 1, count - 1))];
                                        if (_current.Value.Type == CharPosType.NewLine)
                                            _current = _current.Previous;
                                    }
                                }
                            }
                            Scroll(GetPostion().Row);
                        }
                        break;
                    case Keys.Down:
                        {
                            var p = GetPostion();
                            int row = p.Row;
                            int col = p.Column;
                            if (row < _lines.Count - 1)
                            {
                                int count = _lines[row + 1].Count;

                                if (col == -1)
                                {
                                    _current = _lines[row].LastOrDefault();
                                }
                                else
                                {
                                    _current = _lines[row + 1][Math.Max(0, Math.Min(col-1, count - 1))];
                                    if (_current.Value.Type == CharPosType.NewLine)
                                        _current = _current.Previous;
                                }
                            }
                            Scroll(GetPostion().Row);
                        }
                        break;
                    case Keys.Delete:
                        Delete(false);
                        break;
                }
            }

            private void Scroll(int line)
            {
                if (line < StartLine)
                {
                    StartLine = _current?.Value.Line ?? 0;
                }
                else if (line >= StartLine + visualCount)
                {
                    StartLine = line - visualCount + 1;
                }
            }

            public struct CurrentPos
            {
                public int X;
                public int Y;
                public int Row;
                public int Column;
            }

            private Point GetVisualPoint(int x, int y)
            {
                var first = VisualLines.FirstOrDefault()?.FirstOrDefault()?.Value;
                if (first == null)
                {
                    return new Point(x, y);
                }

                return new Point(x, y - first.Y);
            }

            private Point GetRealPoint(int x, int y)
            {
                var first = VisualLines.FirstOrDefault()?.FirstOrDefault()?.Value;
                if (first == null)
                {
                    return new Point(x, y);
                }

                return new Point(x, y + first.Y);
            }

            public CurrentPos GetPostion()
            {
                CurrentPos pos = new CurrentPos()
                {
                    X = 0,
                    Y = 0,
                    Column = -1,
                    Row = 0
                };

                if (_current == null)
                    return pos;

                var last = _current.Value;
                pos.X = last.X + last.Width;
                pos.Y = last.Y;
                pos.Column = last.Column;
                pos.Row = last.Line;

                if (last.Type == CharPosType.NewLine)
                {
                    pos.X = 0;
                    pos.Y += last.Height;
                    pos.Column = -1;
                    pos.Row++;
                }
                else
                {
                    var next = _current?.Next?.Value;
                    if (next != null && next.Line > last.Line)
                    {
                        pos.X = 0;
                        pos.Y = next.Y;
                        pos.Column = -1;
                        pos.Row++;
                    }
                }

                var p = GetVisualPoint(pos.X, pos.Y);
                pos.X = p.X;
                pos.Y = p.Y;
                return pos;
            }

            public void OnMouseDown(MouseEventArgs e)
            {
                var pos  = GetRealPoint(e.X, e.Y);
                foreach (var line in VisualLines)
                {
                    foreach (var n in line)
                    {
                        if (n.Value.Rect.Contains(pos))
                        {
                            if (pos.X < n.Value.X + n.Value.Width / 2)
                                _current = n.Previous;
                            else
                                _current = n;
                            return;
                        }
                    }
                    var last = line.LastOrDefault();
                    if (last != null && pos.Y >= last.Value.Y && pos.Y < last.Value.Y + last.Value.Height)
                    {
                        if (last.Value.Type == CharPosType.NewLine)
                            _current = last.Previous;
                        else
                            _current = last;
                    }
                }
            }

            public T Next
            {
                get
                {
                    LinkedListNode<CharPos<T>> n;
                    if (_current == null)
                    {
                        n = _text.First;
                    }
                    else
                    {
                        n = _current.Next;
                    }
                    if (n == null)
                        return default(T);

                    _current = n;
                    return _current.Value.Holder;
                }
            }

            public T GetChar(int x, int y, out bool isPinyin)
            {
                var pos = GetRealPoint(x, y);
                isPinyin = true;
                foreach (var line in VisualLines)
                {
                    foreach (var n in line)
                    {
                        if (!n.Value.Rect.Contains(pos))
                            continue;

                        if (n.Value.NoteRect.Contains(pos) || n.Value.BeatRect.Contains(pos))
                        {
                            isPinyin = false;
                        }

                        return n.Value.Holder;
                    }
                }
                return default(T);
            }

            public string Text
            {
                get
                {
                    StringBuilder sb = new StringBuilder();
                    var n = _text.First;
                    while (n != null)
                    {
                        sb.Append(n.Value.Holder.Char);
                        n = n.Next;
                    }
                    return sb.ToString();
                }
            }

            public IEnumerable<T> Chars
            {
                get
                {
                    var n = _text.First;
                    while (n != null)
                    {
                        yield return n.Value.Holder;
                        n = n.Next;
                    }
                }
            }

            public string toJson()
            {
                return JsonConvert.SerializeObject(_text, Formatting.Indented);
            }

            public void fromJson(string json)
            {
                _text = JsonConvert.DeserializeObject<LinkedList<CharPos<T>>>(json);
                _current = _text.First;
                GenLines();
            }
        }


        private LinesEditor<LyricChar> editor;

        protected override void OnLoad(EventArgs e)
        {
            m_hImc = ImmGetContext(this.Handle);

            base.OnLoad(e);
            caretTimer.Interval = SystemInformation.CaretBlinkTime;
            caretTimer.Tick += CaretTimer_Tick;

            g = Graphics.FromHwnd(this.Handle);
            editor = new LinesEditor<LyricChar>(Width, Height, Font, PinyinFont, NoteFont, BeatFont, new GraphicsRender(g));

            //VerticalScroll.Enabled = false;
            //VerticalScroll.Visible = true;
        }

        private void CaretTimer_Tick(object sender, EventArgs e)
        {
            HideCaret(Handle);
            ShowCaret(Handle);
        }

        private void SetCaret()
        {
            var p = editor.GetPostion();

            SetCaretPos(p.X, p.Y);
        }

        protected override void OnGotFocus(EventArgs e)
        {
            CreateCaret(Handle, IntPtr.Zero, SystemInformation.CaretWidth, (int)editor.LineHeight);
            ShowCaret(Handle);

            SetCaret();

            caretTimer.Start();

            base.OnGotFocus(e);
        }

        protected override void OnLostFocus(EventArgs e)
        {
            caretTimer.Stop();
            HideCaret(Handle);
            DestroyCaret();

            base.OnLostFocus(e);
        }

        protected override void OnMouseDown(MouseEventArgs e)
        {
            editor.OnMouseDown(e);
            SetCaret();

            base.OnMouseDown(e);
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            editor.Render(new GraphicsRender(e.Graphics));
        }

        protected override void OnPreviewKeyDown(PreviewKeyDownEventArgs e)
        {
            if (e.KeyCode == Keys.Delete 
                || e.KeyCode == Keys.Left 
                || e.KeyCode == Keys.Right 
                || e.KeyCode == Keys.Up 
                || e.KeyCode == Keys.Down)
            {
                editor.OnKeyDown(e.KeyCode);

                SetCaret();

                Invalidate();
                e.IsInputKey = true;
                return;
            }
            base.OnPreviewKeyDown(e);
        }

        private string RemoveTone(string pinyin)
        {
            return pinyin.ToLower().Trim().TrimEnd(new char[] { '0', '1', '2', '3', '4', '5', '6' });
        }

        private int MeasureString(string str, Font font)
        {
            var size = g.MeasureString(str, font);
            return (int)size.Width;
        }

        protected override void WndProc(ref Message m)
        {
            base.WndProc(ref m);
            // the usercontrol will receive a WM_IME_SETCONTEXT message
            // when it gets focused and loses focus respectively
            // when the usercontrol gets focused, the m.WParam is 1
            // when the usercontrol loses focus, the m.WParam is 0
            // only when the usercontrol gets focused, we need to call the
            // IMM function to associate itself to the default input context
            if (m.Msg == WM_IME_SETCONTEXT && m.WParam.ToInt32() == 1)
            {
                Debug.WriteLine("WM_IME_SETCONTEXT");
                ImmAssociateContext(this.Handle, m_hImc);
            }
            else if (m.Msg == WM_CHAR)
            {
                int num = m.WParam.ToInt32();
                char ch = (char)num;
                Debug.WriteLine($"{ch} {num}");

                if (char.IsControl(ch))
                {
                    if (ch == 8)
                    {
                        editor.Delete();
                    }
                    else if (ch == 13)
                    {
                        var lc = new LyricChar() { Char = ch };
                        editor.Append(lc);
                    }
                }
                else
                {
                    LyricChar lc;
                    if (ChineseChar.IsValidChar(ch))
                    {
                        lc = new LyricChar(){ Char = ch };
                        var pinyin = RemoveTone(lc.CChar.Value.Pinyins.FirstOrDefault());
                        lc.Pinyin = pinyin;
                        Debug.WriteLine(lc.CChar.Value.Pinyins.FirstOrDefault());
                        editor.Append(lc);
                    }
                    else
                    {
                        lc = editor.Next;
                        if (lc == null || lc.Char == 13)
                            return;
                        lc.Note = ch;
                        lc.Beat = QuarterNote;
                    }
                }

                SetCaret();
                Invalidate();
            }
            //else if (m.Msg == WM_IME_COMPOSITION)
            //{
            //    var text = CurrentCompStr(this.Handle);
            //    Debug.WriteLine(text);
            //}
            //else if (m.Msg == WM_IME_CHAR)
            //{
            //    Debug.WriteLine((char)m.WParam.ToInt32());
            //}
        }

        public override string Text
        {
            get
            {
                return editor.ToString();
            }
            set
            {
                var str = value;
                foreach (char ch in str)
                {
                    LyricChar lc;
                    if (ChineseChar.IsValidChar(ch))
                    {
                        lc = new LyricChar() { Char = ch };
                        var pinyin = RemoveTone(lc.CChar.Value.Pinyins.FirstOrDefault());
                    }
                    else if (ch == 13)
                    {
                        lc = new LyricChar() { Char = ch };

                    }
                    else
                    {
                        continue;
                    }
                    editor.Append(lc);
                }
            }
        }

        private void LyricsBox_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                LyricChar ch = editor.GetChar(e.X, e.Y, out bool pinyin);
                if (ch == null || ch.CChar.Value == null) 
                    return;

                pinyinChoice.Tag = new { Char = ch, Pinyin = pinyin };
                pinyinChoice.Items.Clear();
                
                if (pinyin)
                {
                    foreach (var py in ch.CChar.Value.Pinyins.Select(s => RemoveTone(s)).Distinct())
                    {
                        pinyinChoice.Items.Add(py);
                    }
                }
                else
                {
                    foreach (var bt in Beats)
                    {
                        pinyinChoice.Items.Add(bt.title);
                    }
                }

                pinyinChoice.Show(this, e.Location);
            }
        }

        public IEnumerable<ILyricChar> Chars => editor.Chars;

        private void pinyinChoice_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {
            var t = e.ClickedItem;
            dynamic tag = pinyinChoice.Tag;
            var ch = tag.Char as LyricChar;
            var pinyin = (bool)tag.Pinyin;
            if (pinyin)
                ch.Pinyin = t.Text;
            else
                ch.Beat = Array.FindIndex(Beats, tp => tp.title == t.Text);
            Invalidate();
        }

        public void SaveFile(string filename)
        {
            File.WriteAllText(filename, editor.toJson());
        }

        public void LoadFile(string filename)
        {
            editor.fromJson(File.ReadAllText(filename));
            Invalidate();
        }

        //public const int WM_IME_COMPOSITION = 0x010F;
        //public const int WM_IME_CHAR = 0x0286;
        //private const int GCS_COMPSTR = 8;
        //[DllImport("Imm32.dll")]
        //public static extern bool ImmReleaseContext(IntPtr hWnd, IntPtr hIMC);
        //[DllImport("Imm32.dll", CharSet = CharSet.Unicode)]
        //private static extern int ImmGetCompositionStringW(IntPtr hIMC, int dwIndex, byte[] lpBuf, int dwBufLen);


        //private string CurrentCompStr(IntPtr handle)
        //{
        //    int readType = GCS_COMPSTR;

        //    //IntPtr hIMC = ImmGetContext(handle);
        //    try
        //    {
        //        int strLen = ImmGetCompositionStringW(m_hImc, readType, null, 0);

        //        if (strLen > 0)
        //        {
        //            byte[] buffer = new byte[strLen];

        //            ImmGetCompositionStringW(m_hImc, readType, buffer, strLen);

        //            return Encoding.Unicode.GetString(buffer);

        //        }
        //        else
        //        {
        //            return string.Empty;
        //        }
        //    }
        //    finally
        //    {
        //        //ImmReleaseContext(handle, hIMC);
        //    }
        //}
    }
}
