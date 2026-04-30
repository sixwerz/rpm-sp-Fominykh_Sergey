using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MySql.Data.MySqlClient;
using MySqlX.XDevAPI;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace avtomat
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            string connString = "Server=127.0.0.1;Port=3306;Database=db;Uid=root;Pwd=1234;";

            string query = "SELECT * FROM users";

            using (MySqlConnection conn = new MySqlConnection(connString))
            {
                conn.Open();
                MySqlDataAdapter adapter = new MySqlDataAdapter(query, conn);

                DataTable dt = new DataTable();
                adapter.Fill(dt);

                dataGridView1.DataSource = dt;
                conn.Close();
            }
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            updateTable();
        }

        public void updateTable() {
            string connString = "Server=127.0.0.1;Port=3306;Database=db;Uid=root;Pwd=1234;";

            string query = "select * from users";

            using (MySqlConnection conn = new MySqlConnection(connString))
            {
                conn.Open();
                MySqlDataAdapter adapter = new MySqlDataAdapter(query, conn);

                DataTable dt = new DataTable();
                adapter.Fill(dt);

                dataGridView1.DataSource = dt;
                conn.Close();
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void button4_Click(object sender, EventArgs e)
        {
            string connString = "Server=127.0.0.1;Port=3306;Database=db;Uid=root;Pwd=1234;";
            using (MySqlConnection conn = new MySqlConnection(connString))
            {
                conn.Open();

                string sql = "INSERT INTO users (login, password) VALUES (@login, @password)";

                using (MySqlCommand command = new MySqlCommand(sql, conn))
                {
                    // Передаём параметры (защита от SQL-инъекций через параметризацию)
                    command.Parameters.AddWithValue("@login", textBox1.Text);
                    command.Parameters.AddWithValue("@password", textBox2.Text);

                    command.ExecuteNonQuery();
                    MessageBox.Show("Данные сохранены!", "Успех", MessageBoxButtons.OK, MessageBoxIcon.Information);

                    textBox1.Clear();
                    textBox2.Clear();

                    updateTable();
                }
            }
        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }

        private void button5_Click(object sender, EventArgs e)
        {
            string connString = "Server=127.0.0.1;Port=3306;Database=db;Uid=root;Pwd=1234;";
            string sql = "DELETE FROM users WHERE id = @id";

            using (MySqlConnection conn = new MySqlConnection(connString))
            {
                conn.Open();
                using (MySqlCommand command = new MySqlCommand(sql, conn))
                {
                    // Передаём ID напрямую (проверка убрана по вашему запросу)
                    command.Parameters.AddWithValue("@id", int.Parse(textBox3.Text.Trim()));

                    int rowsAffected = command.ExecuteNonQuery();

                    if (rowsAffected > 0)
                    {
                        MessageBox.Show("Запись успешно удалена!", "Успех", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        textBox3.Clear();
                    }
                    else
                    {
                        MessageBox.Show("Запись с таким ID не найдена.", "Внимание", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    }

                    updateTable();
                }
            }
        }

        private void button2_Click_1(object sender, EventArgs e)
        {
            string connString = "Server=127.0.0.1;Port=3306;Database=db;Uid=root;Pwd=1234;";

            string query = "SELECT \r\n    c.id AS comment_id,\r\n    c.comment,\r\n    u.id AS user_id,\r\n    u.login\r\nFROM comments c\r\nINNER JOIN users u ON c.fk_user = u.id;";

            using (MySqlConnection conn = new MySqlConnection(connString))
            {
                conn.Open();
                MySqlDataAdapter adapter = new MySqlDataAdapter(query, conn);

                DataTable dt = new DataTable();
                adapter.Fill(dt);

                dataGridView1.DataSource = dt;
                conn.Close();
            }
        }
    }
}
