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

namespace WinVocaloid
{
    public partial class LyricsBox : UserControl
    {
        public LyricsBox()
        {
            InitializeComponent();
            ImeMode = ImeMode.HangulFull;
            Cursor = Cursors.IBeam;
            PinyinFont = new Font(FontFamily.GenericMonospace, 10.0f, FontStyle.Regular);
            Font = new Font(FontFamily.GenericMonospace, 16.0f, FontStyle.Regular);
            SetStyle(ControlStyles.OptimizedDoubleBuffer, true);
            SetStyle(ControlStyles.Selectable, true);
            LineHeight = PinyinFont.Height + Font.Height;
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
        private readonly float LineHeight;
        private int VisualLines;

        private Timer caretTimer = new Timer();
        private Graphics g;

        class LyricChar : IChar
        {
            public char Char { get; set; }
            public string Pinyin { get; set; }
            public ChineseChar CChar { get; set; }
            private int _width;

            public int Width => _width;

            public LyricChar(int width)
            {
                _width = width;
            }
        }


        interface IChar
        {
            char Char { get; }
            int Width { get; }
        }

        enum CharPosType
        {
            None = 0,
            Header = 1,
            NewLine = 2,
        }


        class CharPos<T> where T : IChar
        {
            public CharPos(T ch)
            {
                Type = CharPosType.None;
                Holder = ch;
                if (Holder.Char == 13)
                {
                    Type = CharPosType.NewLine;
                }
            }

            public CharPos()
            {
                Type = CharPosType.Header;
            }


            public CharPosType Type { get; private set; }
            public T Holder { get; private set; }

            public int X { get; set; }
            public int Y { get; set; }
            public int Width { get; set; }
            public int Height { get; set; }
            public int Line { get; set; }
            public int Column { get; set; }

            public Rectangle Rect
            {
                get
                {
                    return new Rectangle(X, Y, Width, Height);
                }
            }
        }

        class LinesEditor<T> where T : IChar
        {
            private LinkedList<CharPos<T>> _text;
            private LinkedListNode<CharPos<T>> _current;

            private List<List<LinkedListNode<CharPos<T>>>> _lines;

            public List<List<LinkedListNode<CharPos<T>>>> Lines => _lines;
            public int Width { get; private set; }
            public int Height { get; private set; }
            public float LineHeight { get; private set; }
            private int visualCount;
            private int StartLine { get; set; }

            public LinesEditor(int width, int height, float lineHeight)
            {
                _text = new LinkedList<CharPos<T>>();
                _lines = new List<List<LinkedListNode<CharPos<T>>>>();

                Width = width;
                Height = height;
                LineHeight = lineHeight;
                visualCount = Height / (int)lineHeight;
                StartLine = 0;
            }

            public List<List<LinkedListNode<CharPos<T>>>> VisualLines
            { 
                get
                {
                    var count = Math.Min(Lines.Count - StartLine, visualCount) ;
                    return Lines.GetRange(StartLine, count);
                }
            }

            public void Append(T ch)
            {
                if (_current != null)
                    _current = _text.AddAfter(_current, new CharPos<T>(ch));
                else
                    _current = _text.AddFirst(new CharPos<T>(ch));

                GenLines();

                Scroll(GetPostion().Row);
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
                    if (c.Holder.Char == 13)
                    {
                        c.Y = (int)y;
                        c.Column = ++col;

                        c.X = (int)x;
                        c.Width = 0;
                        c.Height = (int)LineHeight;
                        c.Line = c.Y / (int)LineHeight;

                        line.Add(n);

                        line = new List<LinkedListNode<CharPos<T>>>();
                        Lines.Add(line);

                        y += LineHeight;
                        x = 0f;
                        col = 0;
                    }
                    else
                    {
                        float w = c.Holder.Width;
                        if (x + w > Width)
                        {
                            y += LineHeight;
                            x = 0f;
                            col = 0;

                            line = new List<LinkedListNode<CharPos<T>>>();
                            Lines.Add(line);
                        }

                        c.Y = (int)y;
                        c.Column = ++col;

                        c.X = (int)x;
                        c.Width = (int)w;
                        c.Height = (int)LineHeight;
                        c.Line = c.Y / (int)LineHeight;
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
                                        _current = _lines[row - 1][Math.Min(col - 1, count - 1)];
                                        if (_current.Value.Holder.Char == 13)
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
                                    _current = _lines[row + 1][Math.Min(col-1, count - 1)];
                                    if (_current.Value.Holder.Char == 13)
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

                if (last.Holder.Char == 13)
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
                            break;
                        }
                    }
                }
            }

            public T GetChar(int x, int y)
            {
                var pos = GetRealPoint(x, y);
                foreach (var line in VisualLines)
                {
                    foreach (var n in line)
                    {
                        if (n.Value.Rect.Contains(pos))
                        {
                            return n.Value.Holder;
                        }
                    }
                }
                return default(T);
            }
        }


        private LinesEditor<LyricChar> editor;

        protected override void OnLoad(EventArgs e)
        {
            m_hImc = ImmGetContext(this.Handle);

            base.OnLoad(e);
            caretTimer.Interval = SystemInformation.CaretBlinkTime;
            caretTimer.Tick += CaretTimer_Tick;

            VisualLines = Height / (int)LineHeight;

            g = Graphics.FromHwnd(this.Handle);
            editor = new LinesEditor<LyricChar>(Width, Height, LineHeight);
        }

        private void CaretTimer_Tick(object sender, EventArgs e)
        {
            HideCaret(Handle);
            ShowCaret(Handle);
        }

        private void SetCaret()
        {
            var p = editor.GetPostion();

            SetCaretPos(p.X, p.Y + PinyinFont.Height);
        }

        protected override void OnGotFocus(EventArgs e)
        {
            CreateCaret(Handle, IntPtr.Zero, SystemInformation.CaretWidth, FontHeight);
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
            var first = editor.VisualLines.FirstOrDefault()?.FirstOrDefault()?.Value;
            if (first == null)
                return;
            foreach (var line in editor.VisualLines)
            {
                foreach (var n in line)
                {
                    var c = n.Value;
                    var s = $"{c.Holder.Char}";
                    var pinyinsize = e.Graphics.MeasureString(c.Holder.Pinyin, PinyinFont);

                    var size = e.Graphics.MeasureString(s, Font);


                    float px = c.X, cx = c.X;
                    if (size.Width > pinyinsize.Width)
                    {
                        px = c.X + (size.Width - pinyinsize.Width) / 2;
                    }
                    else
                    {
                        cx = c.X + (pinyinsize.Width - size.Width) / 2;
                    }

                    if (!string.IsNullOrWhiteSpace(c.Holder.Pinyin))
                    {
                        e.Graphics.DrawString(c.Holder.Pinyin, PinyinFont, Brushes.Black, px, c.Y - first.Y);
                    }

                    e.Graphics.DrawString(s, Font, Brushes.Black, cx, c.Y + PinyinFont.Height - first.Y);
                }
            }
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
                        var lc = new LyricChar(0) { Char = ch };
                        editor.Append(lc);
                    }
                }
                else
                {
                    LyricChar lc;
                    if (ChineseChar.IsValidChar(ch))
                    {
                        var cchar = new ChineseChar(ch);
                        var pinyin = RemoveTone(cchar.Pinyins.FirstOrDefault());

                        int w1 = MeasureString($"{ch}", Font);
                        int w2 = MeasureString(pinyin, PinyinFont);

                        lc = new LyricChar(Math.Max(w1, w2)){ Char = ch, CChar = cchar, Pinyin = pinyin };
                        Debug.WriteLine(cchar.Pinyins.FirstOrDefault());
                    }
                    else
                    {
                        int w1 = MeasureString($"{ch}", Font);
                        lc = new LyricChar(w1){ Char = ch };
                    }

                    editor.Append(lc);
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

        private void LyricsBox_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                LyricChar ch = editor.GetChar(e.X, e.Y);
                if (ch == null || ch.CChar == null) 
                    return;
                pinyinChoice.Tag = ch;
                pinyinChoice.Items.Clear();
                foreach (var py in ch.CChar.Pinyins.Select(s => RemoveTone(s)).Distinct())
                {
                    pinyinChoice.Items.Add(py);
                }
                pinyinChoice.Show(this, e.Location);
            }
        }

        private void pinyinChoice_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {
            var t = e.ClickedItem;
            var ch = pinyinChoice.Tag as LyricChar;
            ch.Pinyin = t.Text;
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
