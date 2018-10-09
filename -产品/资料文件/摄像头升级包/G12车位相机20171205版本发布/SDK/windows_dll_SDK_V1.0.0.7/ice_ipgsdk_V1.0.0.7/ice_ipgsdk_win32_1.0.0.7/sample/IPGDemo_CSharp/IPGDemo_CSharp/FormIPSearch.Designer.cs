namespace IPGDemo_CSharp
{
    partial class FormIPSearch
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.listViewInfo = new System.Windows.Forms.ListView();
            this.button_search = new System.Windows.Forms.Button();
            this.button_ModIp = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // listViewInfo
            // 
            this.listViewInfo.FullRowSelect = true;
            this.listViewInfo.Location = new System.Drawing.Point(12, 57);
            this.listViewInfo.Name = "listViewInfo";
            this.listViewInfo.Size = new System.Drawing.Size(980, 508);
            this.listViewInfo.TabIndex = 0;
            this.listViewInfo.UseCompatibleStateImageBehavior = false;
            this.listViewInfo.View = System.Windows.Forms.View.Details;
            // 
            // button_search
            // 
            this.button_search.Location = new System.Drawing.Point(12, 12);
            this.button_search.Name = "button_search";
            this.button_search.Size = new System.Drawing.Size(75, 23);
            this.button_search.TabIndex = 1;
            this.button_search.Text = "搜索";
            this.button_search.UseVisualStyleBackColor = true;
            this.button_search.Click += new System.EventHandler(this.button_search_Click);
            // 
            // button_ModIp
            // 
            this.button_ModIp.Location = new System.Drawing.Point(145, 12);
            this.button_ModIp.Name = "button_ModIp";
            this.button_ModIp.Size = new System.Drawing.Size(75, 23);
            this.button_ModIp.TabIndex = 2;
            this.button_ModIp.Text = "修改IP";
            this.button_ModIp.UseVisualStyleBackColor = true;
            this.button_ModIp.Click += new System.EventHandler(this.button_ModIp_Click);
            // 
            // FormIPSearch
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1002, 577);
            this.Controls.Add(this.button_ModIp);
            this.Controls.Add(this.button_search);
            this.Controls.Add(this.listViewInfo);
            this.Name = "FormIPSearch";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "FormIPSearch";
            this.Load += new System.EventHandler(this.FormIPSearch_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListView listViewInfo;
        private System.Windows.Forms.Button button_search;
        private System.Windows.Forms.Button button_ModIp;
    }
}