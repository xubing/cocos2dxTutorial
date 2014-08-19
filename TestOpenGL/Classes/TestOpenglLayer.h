//
//  TestOpenglLayer.h
//  TestOpenGL
//
//  Created by Bing-Office on 14-8-19.
//
//

#ifndef __TestOpenGL__TestOpenglLayer__
#define __TestOpenGL__TestOpenglLayer__

#include "cocos2d.h"
//#include "math"

USING_NS_CC_MATH;

class TestOpenglLayer: public cocos2d::Layer{

    public:
    
    static cocos2d::Scene* createScene();
    
    CREATE_FUNC(TestOpenglLayer);
    bool init();
    
    
    virtual void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags) override;
    
    void onDraw();
    public:
    CustomCommand _command;
};

#endif /* defined(__TestOpenGL__TestOpenglLayer__) */
