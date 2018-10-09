<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form 重写 Dispose，以清理组件列表。
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Windows 窗体设计器所必需的
    Private components As System.ComponentModel.IContainer

    '注意: 以下过程是 Windows 窗体设计器所必需的
    '可以使用 Windows 窗体设计器修改它。
    '不要使用代码编辑器修改它。
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.Button1 = New System.Windows.Forms.Button
        Me.Button2 = New System.Windows.Forms.Button
        Me.Button3 = New System.Windows.Forms.Button
        Me.Button4 = New System.Windows.Forms.Button
        Me.Button5 = New System.Windows.Forms.Button
        Me.Button6 = New System.Windows.Forms.Button
        Me.Label1 = New System.Windows.Forms.Label
        Me.Button7 = New System.Windows.Forms.Button
        Me.SuspendLayout()
        '
        'Button1
        '
        Me.Button1.Location = New System.Drawing.Point(12, 1)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(577, 42)
        Me.Button1.TabIndex = 0
        Me.Button1.Text = "设置屏参（注意：只需根据屏的宽高点数的颜色设置一次，发送节目时无需设置）"
        Me.Button1.UseVisualStyleBackColor = True
        '
        'Button2
        '
        Me.Button2.Location = New System.Drawing.Point(12, 49)
        Me.Button2.Name = "Button2"
        Me.Button2.Size = New System.Drawing.Size(577, 42)
        Me.Button2.TabIndex = 1
        Me.Button2.Text = "一个节目下只有一个连接左移的单行文本区域"
        Me.Button2.UseVisualStyleBackColor = True
        '
        'Button3
        '
        Me.Button3.Location = New System.Drawing.Point(12, 97)
        Me.Button3.Name = "Button3"
        Me.Button3.Size = New System.Drawing.Size(577, 42)
        Me.Button3.TabIndex = 2
        Me.Button3.Text = "一个节目下只有一个多行文本区"
        Me.Button3.UseVisualStyleBackColor = True
        '
        'Button4
        '
        Me.Button4.Location = New System.Drawing.Point(12, 145)
        Me.Button4.Name = "Button4"
        Me.Button4.Size = New System.Drawing.Size(577, 42)
        Me.Button4.TabIndex = 3
        Me.Button4.Text = "一个节目下只有一个图片区(表格的显示通过自绘图片并通过此方式添加发送)"
        Me.Button4.UseVisualStyleBackColor = True
        '
        'Button5
        '
        Me.Button5.Location = New System.Drawing.Point(12, 193)
        Me.Button5.Name = "Button5"
        Me.Button5.Size = New System.Drawing.Size(577, 42)
        Me.Button5.TabIndex = 4
        Me.Button5.Text = "一个节目下有一个连续左移的单行文本区和一个数字时钟区(多个区域都通过此方法添加)"
        Me.Button5.UseVisualStyleBackColor = True
        '
        'Button6
        '
        Me.Button6.Location = New System.Drawing.Point(11, 241)
        Me.Button6.Name = "Button6"
        Me.Button6.Size = New System.Drawing.Size(577, 42)
        Me.Button6.TabIndex = 5
        Me.Button6.Text = "两个节目下各有一个单行文本区和一个数字时钟区(多节目通过此方法添加)"
        Me.Button6.UseVisualStyleBackColor = True
        '
        'Label1
        '
        Me.Label1.Location = New System.Drawing.Point(28, 298)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(549, 64)
        Me.Label1.TabIndex = 6
        Me.Label1.Text = "提示：每个按钮下功能代码都是独立的，互不影响，可根据自己的需求选择性去看并更改其中的代码为己用。代码附详细的注示说明，如需demo里没有列出的功能，请查看LedD" & _
            "ll.h文件，内有函数的详细说明,有什么不明白加QQ 2355291262"
        '
        'Button7
        '
        Me.Button7.Location = New System.Drawing.Point(30, 365)
        Me.Button7.Name = "Button7"
        Me.Button7.Size = New System.Drawing.Size(547, 37)
        Me.Button7.TabIndex = 7
        Me.Button7.Text = "test"
        Me.Button7.UseVisualStyleBackColor = True
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 12.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(600, 432)
        Me.Controls.Add(Me.Button7)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.Button6)
        Me.Controls.Add(Me.Button5)
        Me.Controls.Add(Me.Button4)
        Me.Controls.Add(Me.Button3)
        Me.Controls.Add(Me.Button2)
        Me.Controls.Add(Me.Button1)
        Me.Name = "Form1"
        Me.Text = "Form1"
        Me.ResumeLayout(False)

    End Sub
    Friend WithEvents Button1 As System.Windows.Forms.Button
    Friend WithEvents Button2 As System.Windows.Forms.Button
    Friend WithEvents Button3 As System.Windows.Forms.Button
    Friend WithEvents Button4 As System.Windows.Forms.Button
    Friend WithEvents Button5 As System.Windows.Forms.Button
    Friend WithEvents Button6 As System.Windows.Forms.Button
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents Button7 As System.Windows.Forms.Button

End Class
