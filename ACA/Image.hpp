#ifndef ACA_RESOURCE_IMAGE_H
#define ACA_RESOURCE_IMAGE_H

#include "DXImage.h"
#include <string>
#include <Windows.h>

namespace aca { namespace resource {

    //画像クラス。Policyイディオム(=静的なStrategyパターン)を使用
    template<class Policy>
    class Image
    {
    public:
        Image(){}
        Image(std::string fileName, int allNum, POINT divNum, POINT size);

        bool load(std::string fileName);
        bool load(std::string fileName, int allNum, POINT& divNum, POINT& size);
        void draw(POINT& position, bool isTurn = false) const;
        void draw(POINT& position, int index, bool isTurn = false) const;
        int getX() const {return policy.getX();}
        int getY() const {return policy.getY();}

    private:
        Policy policy;
    };

    //デフォルトはDXライブラリを使用
    typedef Image<DXImage> DefaultImage;

    template<class Policy>
    Image<Policy>::Image(std::string fileName, int allNum, POINT divNum, POINT size) : policy(fileName, allNum, divNum, size)
    {
    }

    template<class Policy>
    bool Image<Policy>::load(std::string fileName)
    {
        return policy.load(std::move(fileName));
    }

    template<class Policy>
    bool Image<Policy>::load(std::string fileName, int allNum, POINT& divNum, POINT& size)
    {
        return policy.load(std::move(fileName), allNum, std::move(divNum), std::move(size));
    }

    template<class Policy>
    void Image<Policy>::draw(POINT& position, bool isTurn) const
    {
        policy.draw(std::move(position), isTurn);
    }

    template<class Policy>
    void Image<Policy>::draw(POINT& position, int index, bool isTurn) const
    {
        policy.draw(std::move(position), index, isTurn);
    }

}}

#endif