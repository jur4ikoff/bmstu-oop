#include <QMainWindow>
#include <QString>
#include "ui_interface.h"
#include "SceneFacade.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
private slots:
    void on_fileSelectButton_clicked();
    void on_loadPushButton_clicked();
    void on_cameraAddPushbutton_clicked();
    void on_cameraDeletePushbutton_clicked();
    void on_cameraSetPushbutton_clicked();
    void on_objectMovePushbutton_clicked();
    void on_objectRotatePushbutton_clicked();
    void on_objectScalePushbutton_clicked();
    void on_objectDeletePushbutton_clicked();
    void on_objectCompositePushbutton_clicked();
    void on_undoLastTransformPushbutton_clicked();
    void on_toggleFaceCullingPushbutton_clicked();

private:
    Ui::MainWindow *ui;
    SceneFacade _facade;
    QString _selected_file_path;

    void drawScene();
    void updateCameraList();
    void updateObjectList();
    std::vector<size_t> getSelectedObjectIds();
    std::vector<size_t> getSelectedCameraIds();
    void saveStateBeforeTransform(const std::vector<size_t> &objectIds);
};
