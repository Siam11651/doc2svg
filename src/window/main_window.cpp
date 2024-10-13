#include <window/main_window.hpp>
#include <filesystem>

void d2s::main_window::path_changed(const QString &new_path)
{
    m_path = new_path.toStdString();
}

void d2s::main_window::convert()
{
    m_temp_dir = new QTemporaryDir();

    m_temp_dir->setAutoRemove(true);

    m_pandoc_process->setArguments(
        {
            m_path.c_str(),
            "-o",
            m_temp_dir->path() + "/temp.pdf",
            "-V",
            "geometry:margin=0in"
        }
    );

    m_pandoc_process->start();
}

void d2s::main_window::pdf_generated(const int32_t exit_code, const QProcess::ExitStatus &exit_status)
{
    if(exit_code != 0)
    {
        delete m_temp_dir;

        m_temp_dir = nullptr;

        return;
    }

    m_inkscape_process->setArguments(
        {
            m_temp_dir->path() + "/temp.pdf",
            "--export-plain-svg=" + m_temp_dir->path() + "/temp.svg"
        }
    );

    m_inkscape_process->start();
}

void d2s::main_window::svg_generated(const int32_t exit_code, const QProcess::ExitStatus &exit_status)
{
    if(exit_code != 0)
    {
        delete m_temp_dir;

        m_temp_dir = nullptr;

        return;
    }

    std::filesystem::copy((m_temp_dir->path() + "/temp.svg").toStdString(), m_output_path_edit->text().toStdString(), std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);

    delete m_temp_dir;

    m_temp_dir = nullptr;
}

d2s::main_window::main_window() : QMainWindow()
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
    
    m_svg_viewer = new QSvgWidget();

    m_root_layout->addWidget(m_svg_viewer, 1);

    m_process_layout = new QHBoxLayout();
    
    m_root_layout->addLayout(m_process_layout);

    m_output_path_edit = new QLineEdit();

    m_process_button = new QPushButton();

    m_process_button->setText("Convert");
    m_process_layout->addWidget(m_output_path_edit, 1);
    m_process_layout->addWidget(m_process_button);

    m_pandoc_process = new QProcess();
    m_inkscape_process = new QProcess();

    m_pandoc_process->setProgram(PANDOC_EXE);
    m_inkscape_process->setProgram("inkscape");

    m_error_message = new QErrorMessage();

    m_error_message->setWindowTitle("Conversion Encountered Error");

    setCentralWidget(m_root_widget);
    connect(m_path_edit, &QLineEdit::textChanged, this, &main_window::path_changed);
    connect(m_process_button, &QPushButton::clicked, this, &main_window::convert);
    connect(m_pandoc_process, &QProcess::finished, this, &main_window::pdf_generated);
    connect(m_inkscape_process, &QProcess::finished, this, &main_window::svg_generated);
}

d2s::main_window::~main_window()
{
    delete m_temp_dir;
    delete m_error_message;
    delete m_pandoc_process;
    delete m_path_edit;
    delete m_file_layout;
    delete m_svg_viewer;
    delete m_output_path_edit;
    delete m_process_button;
    delete m_process_layout;
    delete m_root_layout;
    delete m_root_widget;
}