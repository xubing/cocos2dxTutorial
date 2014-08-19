//
//  TestOpenglLayer.cpp
//  TestOpenGL
//
//  Created by Bing-Office on 14-8-19.
//
//

#include "TestOpenglLayer.h"

Scene* TestOpenglLayer::createScene()
{
        // 'scene' is an autorelease object
    auto scene = Scene::create();
    
        // 'layer' is an autorelease object
    auto layer = TestOpenglLayer::create();
    
        // add layer as a child to scene
    scene->addChild(layer);
    
        // return the scene
    return scene;
}

    // on "init" you need to initialize your instance
bool TestOpenglLayer::init()
{
        //////////////////////////////
        // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR));
//    this->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_LABEL_OUTLINE));
    return true;
}

    
void TestOpenglLayer::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
    Layer::visit(renderer, parentTransform, parentFlags);
    
    _command.init(_globalZOrder);
    _command.func = CC_CALLBACK_0(TestOpenglLayer::onDraw, this);
    Director::getInstance()->getRenderer()->addCommand(&_command);
}

void TestOpenglLayer::onDraw()
{
        //获得当前HelloWorld的shader
    auto glProgram = getGLProgram();
        //使用此shader
    glProgram->use();
        //设置该shader的一些内置uniform,主要是MVP，即model-view-project矩阵
    glProgram->setUniformsForBuiltins();
    
    auto size = Director::getInstance()->getWinSize();
        //指定将要绘制的三角形的三个顶点，分别位到屏幕左下角，右下角和正中间的顶端
    float vertercies[] = { 0,0,   //第一个点的坐标
        size.width, 0,   //第二个点的坐标
        size.width / 2, size.height/2};  //第三个点的坐标
        //指定每一个顶点的颜色，颜色值是RGBA格式的，取值范围是0-1
    float color[] = { 0, 1,0, 1,    //第一个点的颜色，绿色
        1,0,0, 1,  //第二个点的颜色, 红色
        0, 0, 1, 1};  //第三个点的颜色， 蓝色
        //激活名字为position和color的vertex attribute
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);
        //分别给position和color指定数据源
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertercies);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, color);
        //绘制三角形，所谓的draw call就是指这个函数调用
    glDrawArrays(GL_TRIANGLES, 0, 3);
        //通知cocos2d-x 的renderer，让它在合适的时候调用这些OpenGL命令
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 3);
        //如果出错了，可以使用这个函数来获取出错信息
    CHECK_GL_ERROR_DEBUG();
}


/*
 Reference: 
 
http://http.developer.nvidia.com/CgTutorial/cg_tutorial_chapter01.html

http://www.opengl-tutorial.org/

http://antongerdelan.net/opengl/index.html

http://www.arcsynthesis.org/gltut/

http://www.scratchapixel.com/

http://duriansoftware.com/joe/An-intro-to-modern-OpenGL.-Chapter-1:-The-Graphics-Pipeline.html
*/