TEMPLATE = app
TARGET = app.exe

QMAKE_CXXFLAGS += -std=c++20
CONFIG += c++20
QT += gui widgets core
OBJECTS_DIR = ./obj
LIBS += -lsqlite3 -L/opt/homebrew/opt/libpq/lib -lpq
QMAKE_CXXFLAGS += -Werror -Wall -Wpedantic -std=c++20 -g

INCLUDEPATH += /opt/homebrew/opt/libpq/include
INCLUDEPATH += $$system(brew --prefix postgresql@14)/include
LIBS += -L$$system(brew --prefix postgresql@14)/lib -lpq
INCLUDEPATH += /opt/homebrew/opt/libpq/include
LIBS += -L/opt/homebrew/opt/libpq/lib -lpq

FORMS = interface.ui

INCLUDEPATH += \ 
src/objects \ 
src/transform \ 
src/visitor \ 
src/square_matrix \ 
src/exception \ 
src/builder \ 
src/reader \ 
src/strategy \ 
src/director \ 
src/concepts \ 
src/manager \ 
src/scene \ 
src/drawer \
src/command/ \
src/command/draw \
src/command/load \
src/command/camera \
src/command/scene \
src/command/object \
src/command/history \
src/facade \
src/database \
src/history \


# Input
HEADERS += \
src/builder/BaseBoneModelBuilder.h \
src/builder/ListBoneModelBuilder.h \
src/builder/MatrixBoneModelBuilder.h \
src/concepts/concept.h \
src/director/BaseDirector.h \
src/director/BaseDirectorCreator.h \
src/director/BaseBoneModelDirector.h \
src/director/Basedirector.h \
src/director/DirectorCreator.h \
src/director/DirectorCreator.hpp \
src/director/DirectorSolution.h \
src/director/ListBoneModelDirector.h \
src/director/MatrixBoneModelDirector.h \
src/drawer/BaseDrawer.h \
src/drawer/BaseDrawerCreator.h \
src/drawer/QtDrawer.h \
src/drawer/QtDrawerCreator.h \
src/exception/baseexception.h \
src/exception/databaseexception.h \
src/exception/matrixexception.h \
src/exception/sqlitereaderexception.h \
src/manager/Drawmanager.hpp \
src/manager/DrawManager.h \
src/manager/LoadManager.h \
src/manager/SceneManager.h \
src/manager/TransformManager.h \
src/objects/BaseModel.h \
src/objects/BoneModel.h \
src/objects/Camera.h \
src/objects/Composite.h \
src/objects/Edge.h \
src/objects/FaceBuilder.h \
src/objects/InvisibleObject.h \
src/objects/ListModelStructure.h \
src/objects/MatrixModelStructure.h \
src/objects/ModelStructure.h \
src/objects/Object.h \
src/objects/Point.h \
src/objects/Vector3.h \
src/objects/VisibleObject.h \
src/reader/BaseReader.h \
src/reader/BaseReaderCreator.h \
src/reader/BoneModelReader.h \
src/reader/ReaderSolution.h \
src/reader/SqliteBoneModelReader.h \
src/reader/PostgresqlBoneModelReader.h \
src/reader/TxtBoneModelReader.h \
src/scene/Scene.h \
src/square_matrix/SquareMatrix.h \
src/square_matrix/SquareMatrix.hpp \
src/square_matrix/SquareMatrixRow.hpp \
src/strategy/CenterStrategy.h \
src/transform/RotateAction.h \
src/transform/ScaleAction.h \
src/transform/ShiftAction.h \
src/transform/TransformAction.h \
src/transform/CameraProjectionAction.h \
src/visitor/Visitor.h \
src/visitor/DrawVisitor.h \
src/main_window.hpp \
src/facade/SceneFacade.h \
src/command/draw/BaseDrawCommand.h \
src/command/draw/DrawSceneQtCommand.h \
src/command/draw/ToggleFaceCullingCommand.h \
src/command/load/TxtLoadCommandDecorator.h \
src/command/load/BaseLoadCommand.h \
src/command/load/MatrixLoadCommand.h \
src/command/load/ListLoadCommand.h \
src/command/load/SqliteLoadCommandDecorator.h \
src/command/load/PostgresqlLoadCommandDecorator.h \
src/command/load/BaseLoadCommandDecorator.h \
src/command/camera/SetCameraCommand.h \
src/command/camera/MoveCameraCommand.h \
src/command/camera/BaseCameraCommand.h \
src/command/camera/RemoveCameraCommand.h \
src/command/camera/AddCameraCommand.h \
src/command/scene/ClearSceneCommand.h \
src/command/scene/BaseSceneCommand.h \
src/command/object/ScaleObjectCommand.h \
src/command/object/BaseObjectCommand.h \
src/command/object/ShiftObjectCommand.h \
src/command/object/RotateObjectCommand.h \
src/command/object/RemoveObjectCommand.h \
src/command/object/CompositeObjectCommand.h \
src/command/BaseCommand.h \
src/command/scene/GetObjectIDsSceneCommand.h \
src/command/scene/GetCameraIDsSceneCommand.h \
src/command/history/BaseHistoryCommand.h \
src/database/DatabaseConnection.h \
src/database/AbstractDatabaseFactory.h \
src/database/SqliteFactory.h \
src/database/PostgresqlFactory.h \
src/database/DatabaseFactoryCreator.h \
src/database/SqliteConnection.h \
src/database/PostgresqlConnection.h \
src/command/CommandManager.h \
src/history/Memento.h \
src/history/CareTaker.h \


SOURCES += ./src/builder/BaseBoneModelBuilder.cpp \
./src/builder/ListBoneModelBuilder.cpp \
./src/builder/MatrixBoneModelBuilder.cpp \
./src/director/BaseBoneModelDirector.cpp \
./src/director/Basedirector.cpp \
./src/director/DirectorSolution.cpp \
./src/director/ListBoneModelDirector.cpp \
./src/director/MatrixBoneModelDirector.cpp \
./src/drawer/BaseDrawer.cpp \
./src/drawer/QtDrawer.cpp \
./src/drawer/BaseDrawerCreator.cpp \
./src/drawer/QtDrawerCreator.cpp \
./src/exception/baseexception.cpp \
./src/manager/LoadManager.cpp \
./src/manager/SceneManager.cpp \
./src/manager/TransformManager.cpp \
./src/manager/DrawManager.cpp \
./src/objects/BaseModel.cpp \
./src/objects/BoneModel.cpp \
./src/objects/Camera.cpp \
./src/objects/Composite.cpp \
./src/objects/Edge.cpp \
./src/objects/FaceBuilder.cpp \
./src/objects/InvisibleObject.cpp \
./src/objects/ListModelStructure.cpp \
./src/objects/MatrixModelStructure.cpp \
./src/objects/ModelStructure.cpp \
./src/objects/Object.cpp \
./src/objects/Point.cpp \
./src/objects/VisibleObject.cpp \
./src/reader/BaseReader.cpp \
./src/reader/BoneModelReader.cpp \
./src/reader/ReaderSolution.cpp \
./src/reader/SqliteBoneModelReader.cpp \
./src/reader/PostgresqlBoneModelReader.cpp \
./src/reader/TxtBoneModelReader.cpp \
./src/scene/Scene.cpp \
./src/strategy/CenterStrategy.cpp \
./src/transform/RotateAction.cpp \
./src/transform/ScaleAction.cpp \
./src/transform/ShiftAction.cpp \
./src/transform/CameraProjectionAction.cpp \
./src/visitor/DrawVisitor.cpp \
./src/main.cpp \
./src/main_window.cpp \
./src/facade/SceneFacade.cpp \
./src/command/BaseCommand.cpp \
./src/transform/TransformAction.cpp \
src/command/camera/SetCameraCommand.cpp \
src/command/camera/MoveCameraCommand.cpp \
src/command/camera/BaseCameraCommand.cpp \
src/command/camera/AddCameraCommand.cpp \
src/command/camera/RemoveCameraCommand.cpp \
src/command/draw/BaseDrawCommand.cpp \
src/command/draw/DrawSceneQtCommand.cpp \
src/command/draw/ToggleFaceCullingCommand.cpp \
src/command/load/MatrixLoadCommand.cpp \
src/command/load/SqliteLoadCommandDecorator.cpp \
src/command/load/PostgresqlLoadCommandDecorator.cpp \
src/command/load/ListLoadCommand.cpp \
src/command/load/BaseLoadCommand.cpp \
src/command/load/BaseLoadCommandDecorator.cpp \
src/command/load/TxtLoadCommandDecorator.cpp \
src/command/object/BaseObjectCommand.cpp \
src/command/object/RotateObjectCommand.cpp \
src/command/object/ShiftObjectCommand.cpp \
src/command/object/ScaleObjectCommand.cpp \
src/command/object/RemoveObjectCommand.cpp \
src/command/object/CompositeObjectCommand.cpp \
src/command/scene/ClearSceneCommand.cpp \
src/command/scene/BaseSceneCommand.cpp \
src/command/scene/GetObjectIDsSceneCommand.cpp \
src/command/scene/GetCameraIDsSceneCommand.cpp \
src/command/history/BaseHistoryCommand.cpp \
src/database/SqliteFactory.cpp \
src/database/PostgresqlFactory.cpp \
src/database/DatabaseFactoryCreator.cpp \
src/database/SqliteConnection.cpp \
src/database/PostgresqlConnection.cpp \
src/command/CommandManager.cpp \
src/history/Memento.cpp \
src/history/CareTaker.cpp
