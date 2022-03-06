Imports System.IO
Imports System.IO.Ports
Imports System.Threading

Public Class Form1
    Shared _continue As Boolean
    Shared _serialPort As SerialPort
    Dim p As String
    Dim a, b As String
    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        TextBox2.Enabled = False
        Me.MaximizeBox = False
        p = InputBox("Enter the COM port", "COM port", "com", 500, 250)
        SerialPort1.Close()
        SerialPort1.PortName = p
        SerialPort1.BaudRate = 9600
        SerialPort1.DataBits = 8
        SerialPort1.Parity = Parity.None
        SerialPort1.StopBits = StopBits.One
        SerialPort1.Handshake = Handshake.None
        SerialPort1.Encoding = System.Text.Encoding.Default
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        TextBox2.Text = "Waiting for responce"
        Dim l As Integer
        l = TextBox1.TextLength
        If l = 10 Then
            a = TextBox1.Text
            TextBox1.Clear()
            SerialPort1.Open()
            SerialPort1.Write(a)
            b = reciveData()
            TextBox2.Text = b
            b = ""
            SerialPort1.Close()

        Else
            TextBox1.Clear()
            TextBox2.Text = "Enter valid number"
        End If
    End Sub

    Public Function reciveData() As String
        Dim x As String
        x = ""
        Do While x = ""
            x = SerialPort1.ReadLine()
        Loop
        Return x
    End Function

    Private Sub TextBox1_Click(sender As Object, e As EventArgs) Handles TextBox1.Click
        TextBox2.Clear()
    End Sub
End Class
