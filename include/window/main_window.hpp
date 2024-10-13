#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QSvgWidget>
#include <QPushButton>
#include <QProcess>
#include <QErrorMessage>
#include <QTemporaryDir>

namespace d2s
{
    class main_window : public QMainWindow
    {
    private:
        std::string m_path = "";
        QTemporaryDir *m_temp_dir = nullptr;
        QProcess *m_pandoc_process = nullptr;
        QProcess *m_inkscape_process = nullptr;
        QWidget *m_root_widget = nullptr;
        QVBoxLayout *m_root_layout = nullptr;
        QHBoxLayout *m_file_layout = nullptr;
        QLineEdit *m_path_edit = nullptr;
        QSvgWidget *m_svg_viewer = nullptr;
        QHBoxLayout *m_process_layout = nullptr;
        QPushButton *m_process_button = nullptr;
        QLineEdit *m_output_path_edit = nullptr;
        QErrorMessage *m_error_message = nullptr;

    private slots:
        void path_changed(const QString &new_path);
        void convert();
        void pdf_generated(const int32_t exit_code, const QProcess::ExitStatus &exit_status);
        void svg_generated(const int32_t exit_code, const QProcess::ExitStatus &exit_status);

    public:
        main_window();
        ~main_window();
    };
}

#endif