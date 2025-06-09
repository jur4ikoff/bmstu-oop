#pragma once
#include "DirectorSolution.h"
#include "ReaderSolution.h"
#include <cstdlib>
#include <memory>

// director_id
#define LIST_BONE_MODEL_DIRECTOR_CREATOR_ID 1
#define MATRIX_BONE_MODEL_DIRECTOR_CREATOR_ID 2

// reader_id
#define TXT_BONE_MODEL_READER_CREATOR_ID 1
#define SQLITE_BONE_MODEL_READER_CREATOR_ID 2
#define POSTGRESQL_BONE_MODEL_READER_CREATOR_ID 3

class LoadManager
{
public:
    LoadManager();
    ~LoadManager() = default;

    std::shared_ptr<Object> LoadBoneModelFile(std::size_t directorID, std::size_t readerID, const char *filename);

protected:
    DirectorSolution _dsolution;
    ReaderSolution _rsolution;
};
