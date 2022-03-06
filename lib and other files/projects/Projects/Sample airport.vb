Public Class Form1
    Dim choise As Integer
    Private Sub RadioButton1_CheckedChanged(sender As Object, e As EventArgs) Handles RadioButton1.CheckedChanged
        Button3.Visible = True
        Label2.Text = "Enter the number"
        Label2.Visible = True
        TextBox1.Clear()
        TextBox1.Visible = True
        Button1.Text = "Write"
        Button1.Visible = True
        Button2.Visible = False
        Label3.Visible = False
        TextBox2.Visible = False
        TextBox2.TextAlign = HorizontalAlignment.Center
        TextBox2.Text = "Waiting for responce"
        RadioButton1.Visible = False
        RadioButton2.Visible = False
        Label1.Visible = False
        Label4.TextAlign = ContentAlignment.TopCenter
        Label4.Text = "welcome to tagging section"
        Label4.Visible = True
        RadioButton1.Checked = False
    End Sub

    Private Sub RadioButton2_CheckedChanged(sender As Object, e As EventArgs) Handles RadioButton2.CheckedChanged
        Button3.Visible=true
        Label2.Text = "Enter the password"
        Label2.Visible = True
        TextBox1.Clear()
        TextBox1.Visible = True
        Button1.Text = "cheak"
        Button1.Visible = True
        Button2.Visible = False
        Label3.Visible = False
        TextBox2.Visible = False
        TextBox2.TextAlign = HorizontalAlignment.Center
        RadioButton1.Visible = False
        RadioButton2.Visible = False
        Label1.Visible = False
        Label4.TextAlign = ContentAlignment.TopCenter
        Label4.Text = "welcome to protection section"
        Label4.Visible = True
        RadioButton2.Checked = False
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        TextBox2.Visible = True
        If TextBox1.TextLength <> 10 Then
            TextBox2.Text = "Enter valid number"
        Else
            TextBox2.Text = "Waiting for responce"
        End If
        Label3.Text = "Status"
        Label3.Visible = True
        Button2.Visible = True

    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        TextBox1.Clear()
        Label3.Visible = False
        TextBox2.Visible = False
        TextBox1.Clear()
        TextBox2.Clear()
        Button2.Visible = False


    End Sub

    Private Sub TextBox1_TextChanged(sender As Object, e As EventArgs) Handles TextBox1.TextChanged

    End Sub

    Private Sub Label4_Click(sender As Object, e As EventArgs) Handles Label4.Click

    End Sub

    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Button3.Click
        If MsgBox("Are you sure", 1, "go back") Then
            Label1.Visible = True
            Label2.Visible = False
            Label3.Visible = False
            Label4.Visible = False
            RadioButton1.Visible = True
            RadioButton1.Checked = False
            RadioButton2.Visible = True
            RadioButton2.Checked = False
            TextBox1.Visible = False
            TextBox1.Clear()
            TextBox2.Clear()
            TextBox2.Visible = False
            Button1.Visible = False
            Button3.Visible = False
        End If

    End Sub
End Class
