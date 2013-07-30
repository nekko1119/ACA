#include "DXImage.h"
#include <stdexcept>
#include <algorithm>
#include <DxLib.h>
using namespace aca::resource;

POINT aca::resource::makePoint(int x, int y)
{
    POINT p = {x, y};
    return p;
}

DXImage::DXImage() : size(makePoint(0, 0)), divNum(0)
{
}

DXImage::DXImage(std::string fileName, int allNum, POINT divNum, POINT size)
{
    load(std::move(fileName), allNum, std::move(divNum), std::move(size));
}

DXImage::~DXImage()
{
}

bool DXImage::load(std::string&& fileName)
{
    divNum = 1;
    handle.resize(1);
    handle.at(0) = LoadGraph(fileName.c_str());

    int x, y;
    GetGraphSize(handle.at(0), &x, &y);
    size.x = x;
    size.y = y;

    return handle.at(0) != 0;
}

bool DXImage::load(std::string&& fileName, int allNum, POINT&& divNum, POINT&& size)
{
    this->divNum = allNum;
    int tempHandle[256];//一時的にハンドルを格納する
    handle.resize(allNum);

    int ret = LoadDivGraph(fileName.c_str(), allNum, divNum.x, divNum.y, size.x, size.y, tempHandle);
    std::copy(tempHandle, tempHandle + allNum, std::begin(handle));

    this->size.x = size.x;
    this->size.y = size.y;

    return ret != 0; 
}

void DXImage::draw(POINT&& position, bool isTurn) const
{
    if(handle.size() == 0)
    {
        return;
    }
    if(!isTurn)
    {
        DrawGraph(position.x, position.y, handle.at(0), TRUE);
    }
    else
    {
        DrawTurnGraph(position.x, position.y, handle.at(0), TRUE);
    }
}

void DXImage::draw(POINT&& position, int index, bool isTurn) const
{
    if(index >= divNum)
    {
        throw std::out_of_range("画像ハンドルが範囲外アクセスされました");
    }

    if(!isTurn)
    {
        DrawGraph(position.x, position.y, handle.at(index), TRUE);
    }
    else
    {
        DrawTurnGraph(position.x, position.y, handle.at(index), TRUE);
    }
}

bool DXImage::hasLoad() const
{
    return divNum != 0;
}