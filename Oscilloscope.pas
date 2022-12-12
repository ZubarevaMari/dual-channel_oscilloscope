program graph;

// подключение библиотеки для работы с виртуальным последовательным портом
uses System.IO.Ports, GraphABC;

const
  freg = 2;
  lengthx = 600;
  lengthy = 600;{Размер окна}
  k = 1; {Изменение амплитуды}

var
  sp{переменная для доступа к порту}: SerialPort;
  s{сообщение}: string;
  x_pr, y0, x, code, i: integer;
  y_pr, y: array [1..2] of integer;

begin
  sp := new SerialPort('COM4');
  sp.Open();
  sp.WriteLine('x');
  
  setWindowsize(lengthy, lengthx);
  ClearWindow(clBlack);
  Pen.Width := 2;
  repeat
    ClearWindow(clBlack);
    x := 50;
    y0 := 180;
    s := sp.ReadLine();
    Val(s, y_pr[1], code);
    s := sp.ReadLine();
    Val(s, y_pr[2], code);
    
    y_pr[1] := round(k*y_pr[1]) + y0;
    y_pr[2] := round(k*y_pr[2]) + y0;
    x_pr := x;
    while x <=550 do
      begin
         s := sp.ReadLine();
         Val(s, y[1], code);
         y[1] := round(k*y[1]) + y0;
         x := x + 25;
         Line(x_pr, y_pr[1], x, y[1], clGreen);
         
         s := sp.ReadLine();
         Val(s, y[2], code);
         y[2] := round(k*y[2]) + y0;
         Line(x_pr, y_pr[2], x, y[2], clRed);
         
         
         x_pr := x;
         for i := 1 to 2 do
             y_pr[i] := y[i];
      end;   
  until false;
  sp.Close();
end.