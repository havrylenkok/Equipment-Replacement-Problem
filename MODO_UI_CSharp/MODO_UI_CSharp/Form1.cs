using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.Threading;

namespace MODO_UI_CSharp
{
    public partial class Form1 : Form
    {

        int qqq = 0, www = 0;
        public Form1()
        {
            InitializeComponent();
           
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int k = 0;
            k = dataGridView1.ColumnCount;
            if (k != 0)
                for (int i = 0; i < k; i++)
                    dataGridView1.Columns.Clear();



            if ((textBox1.Text != "") && (textBox2.Text != ""))
            {
                dataGridView1.ColumnCount = Convert.ToInt32(textBox1.Text) + 2;
                dataGridView1.Rows.Add(3);
                //занесення першого ряду заголовків
                dataGridView1.Rows[0].Cells[0].Value = Convert.ToString("T");
                dataGridView1.Rows[1].Cells[0].Value = Convert.ToString("r ( t )");
                dataGridView1.Rows[2].Cells[0].Value = Convert.ToString("u ( t )");
                for (int i = 0; i < Convert.ToInt32(textBox1.Text) + 1; i++) //заповнення ряду Т(0...n)
                    dataGridView1.Rows[0].Cells[i + 1].Value = i;

                qqq = 1; www = 1;

            }
            else

                MessageBox.Show("Введіть значення перед початком", "Помилка", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if ((textBox1.Text != "") && (textBox2.Text != ""))
            {
                if (qqq == 1 && www == 1)
                {
                    int T = Convert.ToInt32(textBox1.Text);
                    int p = Convert.ToInt32(textBox2.Text);
                    int q = 0, w = 0;

                    for (int i = 0; i <= Convert.ToInt32(textBox1.Text); i++)
                    {
                        if ((Convert.ToString(dataGridView1.Rows[1].Cells[i + 1].Value) == ""))
                            q++;
                    }


                    for (int i = 0; i <= Convert.ToInt32(textBox1.Text); i++)
                    {
                        if ((Convert.ToString(dataGridView1.Rows[2].Cells[i + 1].Value) == ""))
                            w++;
                    }
                    if (w != 0 || q != 0) { MessageBox.Show("Введіть значення !", "Помилка", MessageBoxButtons.OK, MessageBoxIcon.Exclamation); }

                    else
                    {

                        String[] rt_mass = new String[(Convert.ToInt32(textBox1.Text) + 1)];
                        for (int i = 0; i <= Convert.ToInt32(textBox1.Text); i++)
                        {
                            rt_mass[i] = Convert.ToString(dataGridView1.Rows[1].Cells[i + 1].Value) + Convert.ToString(" ");
                        }
                        String rt = String.Concat(rt_mass);//рядок rt

                        String[] ut_mass = new String[(Convert.ToInt32(textBox1.Text) + 1)];
                        for (int i = 0; i <= Convert.ToInt32(textBox1.Text); i++)
                        {
                            ut_mass[i] = Convert.ToString(dataGridView1.Rows[2].Cells[i + 1].Value) + Convert.ToString(" ");
                        }
                        String ut = String.Concat(ut_mass);//рядок ut


                        Process.Start("modo.exe", T + " " + "r" + " " + rt + "u" + " " + ut + p);
                        Thread.Sleep(100);




                        Form2 f = new Form2();
                        f.richTextBox1.LoadFile("temp.txt", RichTextBoxStreamType.PlainText);
                        f.ShowDialog();
                    }
                }
                else { MessageBox.Show("Створіть таблицю!", "Помилка", MessageBoxButtons.OK, MessageBoxIcon.Exclamation); }
            }
            else { MessageBox.Show("Введіть значення перед початком", "Помилка", MessageBoxButtons.OK, MessageBoxIcon.Exclamation); }
	
				
					
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            int num = 0;

            if (Int32.TryParse(textBox1.Text,out num))
            {

            }
            else
            {
                textBox1.Clear();


            }
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

            int num = 0;

            if (Int32.TryParse(textBox2.Text, out num))
            {

            }
            else
            {
                textBox2.Clear();


            }

            

        }

        private void button3_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Автори:\n - Гавриленко Кирило (К)\n - Глущенко Микола\n - Тарасенко Андрій");


        }
    }
}
