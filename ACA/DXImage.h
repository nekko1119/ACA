#ifndef ACA_RESOURCE_DXIMAGE_H
#define ACA_RESOURCE_DXIMAGE_H

#include <string>
#include <vector>
#include <Windows.h>
namespace aca { namespace resource {

//DXライブラリを使用した画像クラス
class DXImage
{
public:
    DXImage();
    DXImage(std::string fileName, int allNum, POINT divNum, POINT size);
    ~DXImage();

    bool load(std::string&& fileName);
    bool load(std::string&& fileName, int allNum, POINT&& divNum, POINT&& size);
    void draw(POINT&& position, bool isTurn = false) const;
    void draw(POINT&& position, int index, bool isTurn = false) const;
    int getX() const {return size.x;}
    int getY() const {return size.y;}

private:
    bool hasLoad() const;

    std::vector<int> handle;	//画像ハンドル
    int divNum;		//分割枚数
    POINT size;		//画像のサイズ
};

POINT makePoint(int x, int y);

}}

#endif