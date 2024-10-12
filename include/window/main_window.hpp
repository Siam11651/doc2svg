#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QProcess>
#include <QErrorMessage>

namespace d2t
{
    class main_window : public QMainWindow
    {
    private:
        std::string m_path = "";
        QProcess *m_converter_process;
        QWidget *m_root_widget = nullptr;
        QVBoxLayout *m_root_layout = nullptr;
        QHBoxLayout *m_file_layout = nullptr;
        QLineEdit *m_path_edit = nullptr;
        QTextEdit *m_output_edit = nullptr;
        QHBoxLayout *m_process_layout = nullptr;
        QPushButton *m_process_button = nullptr;
        QErrorMessage *m_error_message = nullptr;

    private slots:
        void path_changed(const QString &new_path);
        void convert();
        void converted(const int32_t exit_code, const QProcess::ExitStatus &exit_status);

    public:
        main_window();
        ~main_window();
    };
}

#endif