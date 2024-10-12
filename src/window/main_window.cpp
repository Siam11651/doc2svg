#include <window/main_window.hpp>

void d2t::main_window::path_changed(const QString &new_path)
{
    m_path = new_path.toStdString();
}

void d2t::main_window::convert()
{
    m_converter_process->setArguments(
        QStringList(
        {
            "-f",
            "docx",
            "-t",
            "latex",
            m_path.c_str()
        })
    );

    m_converter_process->start();
}

void d2t::main_window::converted(const int32_t exit_code, const QProcess::ExitStatus &exit_status)
{
    if(exit_code == 0)
    {
        m_output_edit->setText(QString(m_converter_process->readAllStandardOutput()));
    }
    else
    {
        m_error_message->showMessage(m_converter_process->readAllStandardError());
    }
}

d2t::main_window::main_window() : QMainWindow()
{
    setWindowTitle("Doc2Tex");
    setMinimumWidth(800);
    setMinimumHeight(600);

    m_root_layout = new QVBoxLayout();
    m_root_widget = new QWidget();

    m_root_widget->setLayout(m_root_layout);

    m_file_layout = new QHBoxLayout();

    m_root_layout->addLayout(m_file_layout);

    m_path_edit = new QLineEdit();

    m_file_layout->addWidget(m_path_edit);
    
    m_output_edit = new QTextEdit();

    m_output_edit->setReadOnly(true);

    m_root_layout->addWidget(m_output_edit, 1);

    m_process_layout = new QHBoxLayout();
    
    m_process_layout->addStretch();
    m_root_layout->addLayout(m_process_layout);

    m_process_button = new QPushButton();

    m_process_button->setText("Convert");
    m_process_layout->addWidget(m_process_button);

    m_converter_process = new QProcess();

    m_converter_process->setProgram(PANDOC_EXE);

    m_error_message = new QErrorMessage();

    m_error_message->setWindowTitle("Conversion Encountered Error");

    setCentralWidget(m_root_widget);
    connect(m_path_edit, &QLineEdit::textChanged, this, &main_window::path_changed);
    connect(m_process_button, &QPushButton::clicked, this, &main_window::convert);
    connect(m_converter_process, &QProcess::finished, this, &main_window::converted);
}

d2t::main_window::~main_window()
{
    delete m_error_message;
    delete m_converter_process;
    delete m_path_edit;
    delete m_file_layout;
    delete m_output_edit;
    delete m_process_button;
    delete m_process_layout;
    delete m_root_layout;
    delete m_root_widget;
}