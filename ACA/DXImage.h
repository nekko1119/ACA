#ifndef ACA_RESOURCE_DXIMAGE_H
#define ACA_RESOURCE_DXIMAGE_H

#include <string>
#include <vector>
#include <Windows.h>
namespace aca { namespace resource {

//DX���C�u�������g�p�����摜�N���X
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

    std::vector<int> handle;	//�摜�n���h��
    int divNum;		//��������
    POINT size;		//�摜�̃T�C�Y
};

POINT makePoint(int x, int y);

}}

#endif