#include <gtk/gtk.h>

// Variables globales
GtkWidget *entry;
double num1 = 0, num2 = 0;
char operator;

// Función para manejar los clics en los botones numéricos
void on_number_clicked(GtkButton *button, gpointer data) {
    const char *current_text = gtk_entry_get_text(GTK_ENTRY(entry));
    const char *button_text = gtk_button_get_label(button);
    char new_text[256];
    snprintf(new_text, sizeof(new_text), "%s%s", current_text, button_text);
    gtk_entry_set_text(GTK_ENTRY(entry), new_text);
}

// Función para manejar los clics en los botones de operadores
void on_operator_clicked(GtkButton *button, gpointer data) {
    const char *current_text = gtk_entry_get_text(GTK_ENTRY(entry));
    num1 = atof(current_text);
    operator = gtk_button_get_label(button)[0];
    gtk_entry_set_text(GTK_ENTRY(entry), "");
}

// Función para manejar el clic en el botón de igual
void on_equal_clicked(GtkButton *button, gpointer data) {
    const char *current_text = gtk_entry_get_text(GTK_ENTRY(entry));
    num2 = atof(current_text);
    double result;

    switch (operator) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            result = num1 / num2;
            break;
        default:
            return;
    }

    char result_text[256];
    snprintf(result_text, sizeof(result_text), "%f", result);
    gtk_entry_set_text(GTK_ENTRY(entry), result_text);
}

// Función para manejar el clic en el botón de limpiar
void on_clear_clicked(GtkButton *button, gpointer data) {
    gtk_entry_set_text(GTK_ENTRY(entry), "");
    num1 = num2 = 0;
    operator = '\0';
}

// Función principal
int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Calculadora");
    gtk_window_set_default_size(GTK_WINDOW(window), 250, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 4, 1);

    const char *buttons[4][4] = {
        {"7", "8", "9", "/"},
        {"4", "5", "6", "*"},
        {"1", "2", "3", "-"},
        {"0", "C", "=", "+"}
    };

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            GtkWidget *button = gtk_button_new_with_label(buttons[i][j]);
            gtk_grid_attach(GTK_GRID(grid), button, j, i+1, 1, 1);

            if (buttons[i][j][0] >= '0' && buttons[i][j][0] <= '9') {
                g_signal_connect(button, "clicked", G_CALLBACK(on_number_clicked), NULL);
            } else if (buttons[i][j][0] == 'C') {
                g_signal_connect(button, "clicked", G_CALLBACK(on_clear_clicked), NULL);
            } else if (buttons[i][j][0] == '=') {
                g_signal_connect(button, "clicked", G_CALLBACK(on_equal_clicked), NULL);
            } else {
                g_signal_connect(button, "clicked", G_CALLBACK(on_operator_clicked), NULL);
            }
        }
    }

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
