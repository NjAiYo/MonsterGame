//
//  FilterSprite.h
//  MonsterGame
//
//  Created by John Running on 15/5/15.
//
//

#ifndef __MonsterGame__FilterSprite__
#define __MonsterGame__FilterSprite__

#include "cocos2d.h"

USING_NS_CC;


class FilterSprite : public Sprite{
    
public:
    
    FilterSprite();
    virtual ~FilterSprite();
    
    static FilterSprite* create();
    static FilterSprite* create(const std::string& filename);
    static FilterSprite* create(const std::string& filename, const Rect& rect);
    
    
    static FilterSprite* createWithTexture(Texture2D *pTexture);
    static FilterSprite* createWithTexture(Texture2D *pTexture, const Rect& rect, bool rotated=false);
    static FilterSprite* createWithSpriteFrame(SpriteFrame *pSpriteFrame);
    static FilterSprite* createWithSpriteFrameName(const std::string& spriteFrameName);
    
    bool initWithTexture(Texture2D* pTexture, const Rect& tRect);
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    void onDraw(const Mat4 &transform, uint32_t flags);
    void setFilterMat(cocos2d::Mat4 matrixArray);
    //to-do 提供一个设置滤镜的方法
protected:
    CustomCommand _customCommand;
private:
    cocos2d::Mat4   m_uSpriteFilter;
};
#endif /* defined(__MonsterGame__FilterSprite__) */
