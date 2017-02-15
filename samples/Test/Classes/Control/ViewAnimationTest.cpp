
#include "ViewAnimationTest.h"
#include "CDUIShowAutoCollectionView.h"

int AnimationNum = 0;

ViewAnimationTest::ViewAnimationTest()
{
    CADrawerController* drawer = (CADrawerController*)CAApplication::getApplication()->getRootWindow()->getRootViewController();
    drawer->setTouchMoved(false);
}

ViewAnimationTest::~ViewAnimationTest()
{
    CADrawerController* drawer = (CADrawerController*)CAApplication::getApplication()->getRootWindow()->getRootViewController();
    drawer->setTouchMoved(true);
    AnimationNum = 0;
}

void CDUIShowAutoCollectionView::ViewAnimationRightBtnRightcallback(CAButton* btn)
{
    if (showViewAnimationNavigationBar >= 2)
    {
        showViewAnimationNavigationBar = 0;
        AnimationNum = showViewAnimationNavigationBar;
    }
    else
    {
        AnimationNum = ++showViewAnimationNavigationBar;
    }
    ViewAnimationTest* ViewContrllerViewAnimationTest = new ViewAnimationTest();
    ViewContrllerViewAnimationTest->init();
    ViewContrllerViewAnimationTest->setNavigationBarItem(ViewAnimationNavigationBar);
    ViewContrllerViewAnimationTest->autorelease();
    RootWindow::getInstance()->getRootNavigationController()->replaceViewController(ViewContrllerViewAnimationTest, false);
}

void ViewAnimationTest::viewDidLoad()
{
    winSize = this->getView()->getBounds().size;
    winRect = this->getView()->getBounds();
    
    if (AnimationNum == 0)
    {
        //Animation 1
        heart_index = 0;
        CAButton* btn1 = CAButton::create(CAButton::Type::RoundedRect);
        btn1->setLayout(DLayout(DHorizontalLayout_W_C(240, 0.5), DVerticalLayout_H_C(56, 0.25)));
        btn1->setTitleForState(CAControl::State::Normal, "Play Animation");
        btn1->setTitleColorForState(CAControl::State::Normal, ccc4(51,204,255,255));
        btn1->setTag(100);
        btn1->addTarget([=](CAButton* btn)
        {
            animation_1_view->setScale(1);
            CAViewAnimation::beginAnimations("");
            CAViewAnimation::setAnimationDuration(0.3f);
            CAViewAnimation::setAnimationRepeatAutoreverses(true);
            
            if (heart_index==0) {
                animation_1_view->setImage(CAImage::create("image/heart2.png"));
                heart_index = 1;
            }else{
                animation_1_view->setImage(CAImage::create("image/heart1.png"));
                heart_index = 0;
            }
            
            animation_1_view->setScale(2);
            
            CAViewAnimation::commitAnimations();
        }, CAButton::Event::TouchUpInSide);
        animation_1_view = CAImageView::createWithLayout(DLayout(DHorizontalLayout_W_C(28, 0.5), DVerticalLayout_H_C(24, 0.5)));
        animation_1_view->setImage(CAImage::create("image/heart1.png"));
    
        CAView* view1 = CAView::createWithLayout(DLayoutFill);
        view1->addSubview(btn1);
        view1->addSubview(animation_1_view);
        view1->setColor(CAColor_gray);
        this->getView()->addSubview(view1);
    }
    else if (AnimationNum == 1)
    {
        //Animation 2
        CAImageView* bg = CAImageView::createWithLayout(DLayout(DHorizontalLayoutFill, DVerticalLayout_H_C(80, 0.5)));
        bg->setImage(CAImage::create("image/navbg.jpg"));
    
        animation_2_textfield = CATextField::createWithLayout(DLayout(DHorizontalLayout_L_R(90, 90), DVerticalLayout_H_C(50, 0.5)));
        animation_2_textfield->setFontSize(40);
        animation_2_textfield->setKeyboardType(CATextField::KeyboardType::Default);
        animation_2_textfield->setVisible(false);
        
        animation_2_btn_search = CAButton::createWithLayout(DLayout(DHorizontalLayout_L_W(25, 56), DVerticalLayout_H_C(48, 0.5)), CAButton::Type::Custom);
        animation_2_btn_search->setImageForState(CAControl::State::Normal, CAImage::create("image/search_btn.png"));
        animation_2_btn_search->setTag(201);
        animation_2_btn_search->addTarget([=](CAButton* btn)
        {
            animation_2_textfield->setVisible(true);
            animation_2_btn_cancel->setVisible(false);
            animation_2_textfield->setAlpha(0);
            animation_2_textfield->setLayout(DLayout(DHorizontalLayout_L_R(90, 90), DVerticalLayout_H_C(50, 0.5)));
            
            CAViewAnimation::beginAnimations("");
            CAViewAnimation::setAnimationDuration(0.3f);
            animation_2_textfield->setLayout(DLayout(DHorizontalLayout_L_R(90, 90), DVerticalLayout_H_C(50, 0.5)));
            animation_2_textfield->setAlpha(1);
            CAViewAnimation::setAnimationDidStopSelector([=]()
            {
                if (animation_2_btn_cancel->isVisible()) {
                    animation_2_btn_cancel->setVisible(false);
                }else{
                    animation_2_btn_cancel->setVisible(true);
                }
            });
            CAViewAnimation::commitAnimations();
        }, CAButton::Event::TouchUpInSide);
        
    
        animation_2_btn_cancel = CAButton::createWithLayout(DLayout(DHorizontalLayout_R_W(0, 100), DVerticalLayout_H_C(50, 0.5)), CAButton::Type::Custom);
        animation_2_btn_cancel->setTitleForState(CAControl::State::Normal, "Cancel");
        animation_2_btn_cancel->setTag(202);
        animation_2_btn_cancel->setTitleColorForState(CAControl::State::Normal, CAColor_white);
        animation_2_btn_cancel->addTarget([=](CAButton* btn)
        {
            CAViewAnimation::beginAnimations("");
            CAViewAnimation::setAnimationDuration(0.3f);
            animation_2_textfield->setLayout(DLayout(DHorizontalLayout_L_W(90, 0), DVerticalLayout_H_C(50, 0.5)));
            animation_2_textfield->setAlpha(0);
            CAViewAnimation::setAnimationDidStopSelector([=]()
            {
                if (animation_2_btn_cancel->isVisible()) {
                    animation_2_btn_cancel->setVisible(false);
                }else{
                    animation_2_btn_cancel->setVisible(true);
                }
            });
            CAViewAnimation::commitAnimations();
        }, CAButton::Event::TouchUpInSide);
        animation_2_btn_cancel->setVisible(false);
    
        CAView* view2 = CAView::createWithLayout(DLayoutFill);
        view2->addSubview(bg);
        view2->addSubview(animation_2_textfield);
        view2->addSubview(animation_2_btn_search);
        view2->addSubview(animation_2_btn_cancel);
        view2->setColor(CAColor_gray);
        this->getView()->addSubview(view2);
    }
    else
    {
        //Animation 3
        animation_3_imageview = CAImageView::createWithLayout(DLayoutFill);
        animation_3_imageview->setImage(CAImage::create("image/2.jpg"));
    
        CAButton* btn3 = CAButton::create(CAButton::Type::RoundedRect);
        btn3->setLayout(DLayout(DHorizontalLayout_W_C(240, 0.5), DVerticalLayout_H_C(56, 0.25)));
        btn3->setTitleForState(CAControl::State::Normal, "Play Animation");
        btn3->setTitleColorForState(CAControl::State::Normal, ccc4(51,204,255,255));
        btn3->setTag(300);
        btn3->addTarget([=](CAButton* btn)
        {
            DSize imageSize = CAImage::create("image/2.jpg")->getContentSize();
            
            animation_3_imageview->setImageRect(DRect(0,0,0,imageSize.height));
            animation_3_imageview->setLayout(DLayout(DHorizontalLayout_L_W(0, 0), DVerticalLayoutFill));
            CAViewAnimation::beginAnimations("");
            CAViewAnimation::setAnimationDuration(0.8f);
            CAViewAnimation::setAnimationRepeatAutoreverses(true);
            animation_3_imageview->setImageRect(DRect(0,0,imageSize.width,imageSize.height));
            animation_3_imageview->setLayout(DLayout(DHorizontalLayout_L_R(0, 0), DVerticalLayoutFill));
            CAViewAnimation::commitAnimations();
        }, CAButton::Event::TouchUpInSide);
    
        CAView* view3 = CAView::createWithLayout(DLayoutFill);
        view3->addSubview(animation_3_imageview);
        view3->addSubview(btn3);
        view3->setColor(CAColor_gray);
        this->getView()->addSubview(view3);
    }

}

void ViewAnimationTest::viewDidUnload()
{
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}
