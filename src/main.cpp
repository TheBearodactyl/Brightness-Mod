#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>

using namespace geode::prelude;

class Brightness : public FLAlertLayer {
    CCTextInputNode* minInput;
    CCTextInputNode* maxInput;
    CCTextInputNode* randInput;
public:
	bool init() {
        if (!initWithColor({ 0, 0, 0, 150 })) return false;

        this->setID("BrightnessPopup"_spr);

        cocos2d::CCTouchDispatcher::get()->registerForcePrio(this, 2);

        this->setKeypadEnabled(true);
        this->setTouchEnabled(true);

        auto size = CCDirector::sharedDirector()->getWinSize();

        m_mainLayer = CCLayer::create();
        m_buttonMenu = CCMenu::create();
        m_buttonMenu->setPosition({0,0});

        auto bg = extension::CCScale9Sprite::create("GJ_square01.png");
        bg->setContentSize({ 320, 280 });
        bg->setPosition({ size.width / 2, size.height / 2 });
        m_mainLayer->addChild(bg, -1);

        auto titulo = CCLabelBMFont::create("Brightness Options", "bigFont.fnt");
        titulo->setScale(.7);
        titulo->setPosition({ bg->getPositionX(), bg->getPositionY() + bg->getContentSize().height / 2 - 16 });
        m_mainLayer->addChild(titulo);

        auto line = CCSprite::createWithSpriteFrameName("floorLine_001.png");
        line->setBlendFunc({GL_SRC_ALPHA, GL_ONE});
        line->setScaleX(.7);
        line->setOpacity(100);
        line->setPosition({ titulo->getPositionX(), titulo->getPositionY() - 17 });
        m_mainLayer->addChild(line);

        auto sub = CCLabelBMFont::create("Min.", "goldFont.fnt");
        sub->setScale(.65);
        sub->setPosition({ size.width / 2 - 75, line->getPositionY() - 20 });
        m_mainLayer->addChild(sub);

        auto nodeBG = extension::CCScale9Sprite::create("square02_small.png");
        nodeBG->setContentSize({ 65, 28 });
        nodeBG->setOpacity(120);
        nodeBG->setPosition({ sub->getPositionX(), sub->getPositionY() - 25 });
        m_mainLayer->addChild(nodeBG);

        minInput = CCTextInputNode::create(50, 40, "Num", "bigFont.fnt");
        minInput->setPosition({ nodeBG->getPositionX(), nodeBG->getPositionY() });
        minInput->setMaxLabelScale(.5f);
        minInput->setAllowedChars("0123456789.-");
        minInput->setLabelPlaceholderColor({ 120, 170, 240 });
        minInput->setLabelPlaceholderScale(.5f);
        minInput->setMaxLabelLength(5);
        minInput->setString(CCString::createWithFormat("%.02f", static_cast<float>(Mod::get()->getSettingValue<double>("min-brightness")))->getCString());
        m_mainLayer->addChild(minInput);
        minInput->setTouchPriority(-502);

        auto sub2 = CCLabelBMFont::create("Max.", "goldFont.fnt");
        sub2->setScale(.65);
        sub2->setPosition({ size.width / 2, line->getPositionY() - 20 });
        m_mainLayer->addChild(sub2);

        auto nodeBG2 = extension::CCScale9Sprite::create("square02_small.png");
        nodeBG2->setContentSize({ 65, 28 });
        nodeBG2->setOpacity(120);
        nodeBG2->setPosition({ sub2->getPositionX(), sub2->getPositionY() - 25 });
        m_mainLayer->addChild(nodeBG2);

        maxInput = CCTextInputNode::create(50, 40, "Num", "bigFont.fnt");
        maxInput->setPosition({ nodeBG2->getPositionX(), nodeBG2->getPositionY() });
        maxInput->setMaxLabelScale(.5f);
        maxInput->setAllowedChars("0123456789.-");
        maxInput->setLabelPlaceholderColor({ 120, 170, 240 });
        maxInput->setLabelPlaceholderScale(.5f);
        maxInput->setMaxLabelLength(5);
        maxInput->setString(CCString::createWithFormat("%.02f", static_cast<float>(Mod::get()->getSettingValue<double>("max-brightness")))->getCString());
        m_mainLayer->addChild(maxInput);
        maxInput->setTouchPriority(-502);

        auto sub3 = CCLabelBMFont::create("Random", "goldFont.fnt");
        sub3->setScale(.65);
        sub3->setPosition({ size.width / 2 + 75, line->getPositionY() - 20 });
        m_mainLayer->addChild(sub3);

        auto nodeBG3 = extension::CCScale9Sprite::create("square02_small.png");
        nodeBG3->setContentSize({ 65, 28 });
        nodeBG3->setOpacity(120);
        nodeBG3->setPosition({ sub3->getPositionX(), sub3->getPositionY() - 25 });
        m_mainLayer->addChild(nodeBG3);

        randInput = CCTextInputNode::create(50, 40, "Num", "bigFont.fnt");
        randInput->setPosition({ nodeBG3->getPositionX(), nodeBG3->getPositionY() });
        randInput->setMaxLabelScale(.5f);
        randInput->setAllowedChars("0123456789.-");
        randInput->setLabelPlaceholderColor({ 120, 170, 240 });
        randInput->setLabelPlaceholderScale(.5f);
        randInput->setMaxLabelLength(5);
        randInput->setString(CCString::createWithFormat("%.02f", static_cast<float>(Mod::get()->getSettingValue<double>("randomness")))->getCString());
        m_mainLayer->addChild(randInput);
        randInput->setTouchPriority(-502);

        auto whatColor = CCLabelBMFont::create("What color", "goldFont.fnt");
        whatColor->setScale(.65);
        whatColor->setPosition({ size.width / 2, bg->getPositionY() + 30 });
        m_mainLayer->addChild(whatColor);

        auto type = CCLabelBMFont::create("Width & height", "goldFont.fnt");
        type->setScale(.65);
        type->setPosition({ size.width / 2, bg->getPositionY() - 30 });
        m_mainLayer->addChild(type);

        for (int i = 0; i < 3; i++) {
            auto tog = CCMenuItemToggler::create(this->getButtonSprite(i, false), this->getButtonSprite(i, true), this, menu_selector(Brightness::onToggle));
            tog->setPosition({ bg->getPositionX() - 75.f + 75.f * i, whatColor->getPositionY() - 30 });
            tog->setTag(i);
            tog->setClickable(false);
            m_buttonMenu->addChild(tog);

            if (i == static_cast<int>(Mod::get()->getSettingValue<int64_t>("what-color")))
                tog->toggle(true);

            auto tog2 = CCMenuItemToggler::create(this->getButtonSprite(i, false, true), this->getButtonSprite(i, true, true), this, menu_selector(Brightness::onToggle2));
            tog2->setPosition({ bg->getPositionX() - 75.f + 75.f * i, type->getPositionY() - 30 });
            tog2->setTag(i + 10);
            tog2->setClickable(false);
            m_buttonMenu->addChild(tog2);

            if (i == static_cast<int>(Mod::get()->getSettingValue<int64_t>("type")))
                tog2->toggle(true);
        }

        auto toggle = CCMenuItemToggler::createWithStandardSprites(this, menu_selector(Brightness::onInvert), 0.7f);
        toggle->setPosition({ bg->getPositionX() - bg->getContentSize().width / 2 + 25, bg->getPositionY() - bg->getContentSize().height / 2 + 25 });
        toggle->toggle(Mod::get()->getSettingValue<bool>("invert-brightness"));
        m_buttonMenu->addChild(toggle);

        auto invert = CCLabelBMFont::create("Invert", "bigFont.fnt");
        invert->setScale(.45f);
        invert->setAnchorPoint({0, 0.5f});
        invert->setPosition({ toggle->getPositionX() + 20, toggle->getPositionY() });
        m_mainLayer->addChild(invert);

        auto closeBtn = CCMenuItemSpriteExtra::create(ButtonSprite::create("Ok", 40.0f, true, "goldFont.fnt", "GJ_button_01.png", 30.0f, 0.8f), this, menu_selector(Brightness::onClose));
        closeBtn->setPosition({ bg->getPositionX(), bg->getPositionY() - bg->getContentSize().height / 2 + 25 });
        m_buttonMenu->addChild(closeBtn);

        m_mainLayer->addChild(m_buttonMenu);
        this->addChild(m_mainLayer);

        return true;
	}
    void onToggle(CCObject* s) {
        auto tag = reinterpret_cast<CCMenuItemToggler*>(s)->getTag();
        for (int i = 0; i < 3; i++)
            reinterpret_cast<CCMenuItemToggler*>(m_buttonMenu->getChildByTag(i))->toggle(false);

        reinterpret_cast<CCMenuItemToggler*>(m_buttonMenu->getChildByTag(tag))->toggle(true);
        Mod::get()->setSettingValue<int64_t>("what-color", tag);
    }
    void onToggle2(CCObject* s) {
        auto tag = reinterpret_cast<CCMenuItemToggler*>(s)->getTag();
        for (int i = 0; i < 3; i++)
            reinterpret_cast<CCMenuItemToggler*>(m_buttonMenu->getChildByTag(i + 10))->toggle(false);

        reinterpret_cast<CCMenuItemToggler*>(m_buttonMenu->getChildByTag(tag))->toggle(true);
        Mod::get()->setSettingValue<int64_t>("type", tag - 10);
    }
    ButtonSprite* getButtonSprite(int id, bool activated, bool alt = false) {
        const char* text = "Base";
        const char* buttonSprite = "GJ_button_04.png";

        if (alt) {
            if (activated) buttonSprite = "GJ_button_03.png";
            switch (id) {
                case 1: text = "Radial"; break;
                case 2: text = "Linear"; break;
                default: text = "None"; break;
            }
        }
        else {
            if (activated) buttonSprite = "GJ_button_02.png";
            switch (id) {
                case 1: text = "Detail"; break;
                case 2: text = "Both"; break;
            }
        }
        return ButtonSprite::create(text, 50, 0, "bigFont.fnt", buttonSprite, 30, 0.5);
    }
    void keyBackClicked() {
        this->onClose(nullptr);
    }
    void onClose(CCObject*) {
        Mod::get()->setSettingValue<double>("min-brightness", atof(minInput->getString().c_str()));
        Mod::get()->setSettingValue<double>("max-brightness", atof(maxInput->getString().c_str()));
        Mod::get()->setSettingValue<double>("randomness", atof(randInput->getString().c_str()));

        this->setTouchEnabled(false);
        this->setKeypadEnabled(false);

        Brightness::onBtn1(nullptr);
    }
    void onInvert(CCObject*) {
        Mod::get()->setSettingValue<bool>("invert-brightness", !Mod::get()->getSettingValue<bool>("invert-brightness"));
    }
    void onCenter(CCObject*) {
        Mod::get()->setSettingValue<bool>("from-center", !Mod::get()->getSettingValue<bool>("from-center"));
    }
    void adjustBrightness(GameObject* gameObj, float minBrightness, float maxBrightness, float randomness, bool invertBrightness, int whatColor, float imageWidth, float imageHeight, float centerX, float centerY, float minYPos) {
        float baseBrightness = 0;
        
        switch (static_cast<int>(Mod::get()->getSettingValue<int64_t>("type"))) {
            case 1:{ // radial
                float distanceToCenter = ccpDistance(gameObj->getPosition(), ccp(centerX, centerY));
                float normalizedDistance = distanceToCenter / (std::max(imageWidth, imageHeight) / 2.0f);
                baseBrightness = invertBrightness ? minBrightness * normalizedDistance + maxBrightness * (1 - normalizedDistance) : maxBrightness * normalizedDistance + minBrightness * (1 - normalizedDistance);
                }break;
            case 2:{ // lineal
                float interpolationFactor = std::max(std::abs(gameObj->getPositionX() - centerX), std::abs(gameObj->getPositionY() - centerY)) / std::max(imageWidth, imageHeight);
                baseBrightness = invertBrightness ? (minBrightness - 1) * interpolationFactor + maxBrightness * (1 - interpolationFactor) : (maxBrightness * 2) * interpolationFactor + minBrightness * (1 - interpolationFactor);
                }break;
            default:{ // none
                float interpolationFactor = 1.0f - (gameObj->getPositionY() - minYPos) / imageHeight;
                baseBrightness = invertBrightness ? maxBrightness * interpolationFactor + minBrightness * (1 - interpolationFactor) : minBrightness * interpolationFactor + maxBrightness * (1 - interpolationFactor);
                }break;
        } 

        float randomizedBrightness = baseBrightness + (static_cast<float>(std::rand()) / RAND_MAX - 0.5f) * 2 * randomness;
        float clampedBrightness = std::max(minBrightness, std::min(maxBrightness, randomizedBrightness));

        switch (whatColor) {
            case 1:
                if (gameObj->m_detailColor)
                    gameObj->m_detailColor->m_hsv.absoluteBrightness = clampedBrightness;
                break;
            case 2:
                gameObj->m_baseColor->m_hsv.absoluteBrightness = clampedBrightness;
                if (gameObj->m_detailColor)
                    gameObj->m_detailColor->m_hsv.absoluteBrightness = clampedBrightness;
                break;
            default:
                gameObj->m_baseColor->m_hsv.absoluteBrightness = clampedBrightness;
                break;
        }
    }
    void onAutomatic(CCObject*) {
        if (!CCDirector::sharedDirector()->getRunningScene()->getChildByID("BrightnessPopup"_spr)) {
            auto selectedObjects = GameManager::sharedState()->getEditorLayer()->m_editorUI->getSelectedObjects();
        
            if (selectedObjects->count() > 0) {
                float minBrightness = static_cast<float>(Mod::get()->getSettingValue<double>("min-brightness"));
                float maxBrightness = static_cast<float>(Mod::get()->getSettingValue<double>("max-brightness"));
                float randomness = static_cast<float>(Mod::get()->getSettingValue<double>("randomness"));
                bool invertBrightness = Mod::get()->getSettingValue<bool>("invert-brightness");
                int whatColor = static_cast<int>(Mod::get()->getSettingValue<int64_t>("what-color"));

                if (minBrightness > maxBrightness && maxBrightness < minBrightness) {
                    std::swap(minBrightness, maxBrightness);
                    invertBrightness = !invertBrightness;
                }

                float minXPos = std::numeric_limits<float>::max();
                float maxXPos = std::numeric_limits<float>::lowest();
                float minYPos = std::numeric_limits<float>::max();
                float maxYPos = std::numeric_limits<float>::lowest();

                for (int i = 0; i < selectedObjects->count(); ++i) {
                    auto sprite = reinterpret_cast<GameObject*>(selectedObjects->objectAtIndex(i));
                    float spriteX = sprite->getPositionX();
                    float spriteY = sprite->getPositionY();

                    minXPos = std::min(minXPos, spriteX);
                    maxXPos = std::max(maxXPos, spriteX);
                    minYPos = std::min(minYPos, spriteY);
                    maxYPos = std::max(maxYPos, spriteY);
                }

                float imageWidth = maxXPos - minXPos;
                float imageHeight = maxYPos - minYPos;
                float centerX = minXPos + imageWidth * 0.5f;
                float centerY = minYPos + imageHeight * 0.5f;

                for (int i = 0; i < selectedObjects->count(); ++i) {
                    auto sprite = dynamic_cast<GameObject*>(selectedObjects->objectAtIndex(i));
                    adjustBrightness(sprite, minBrightness, maxBrightness, randomness, invertBrightness, whatColor, imageWidth, imageHeight, centerX, centerY, minYPos);
                }
            } else {
                Brightness::create()->show();
            }
        }
    }
    static Brightness* create() {
        auto r = new Brightness;
        if (r && r->init()) {
            r->autorelease();
            r->m_noElasticity = true;
        }
        else CC_SAFE_DELETE(r);
        return r;
    }
};

float m_defaultTime = 1.0f;
class CustomButton : public CCMenuItemSpriteExtra {
public:
    CCLabelBMFont* m_timeLabel;
    float m_time;
    float m_waitTime;

public:
    static CustomButton* create(CCNode* p0, CCObject* p1, SEL_MenuHandler p2) {
        return (CustomButton*)CCMenuItemSpriteExtra::create(p0, p1, p2);
    }
    void setup() {
        m_time = m_defaultTime;
        m_timeLabel = CCLabelBMFont::create(CCString::createWithFormat("%.02fs", m_time)->getCString(), "goldFont.fnt");
        m_timeLabel->limitLabelWidth(25, 0.5f, 0);
        m_timeLabel->setPositionX(m_pNormalImage->getScaledContentSize().width / 2);
        #ifdef GEODE_IS_WINDOWS
            m_timeLabel->setPositionY(m_pNormalImage->getScaledContentSize().height / 2);
        #else
            m_timeLabel->setPositionY(m_pNormalImage->getScaledContentSize().height + 10);
        #endif

        this->addChild(m_timeLabel);

        this->schedule(schedule_selector(CustomButton::_update));
    }
    void _update(float dt) {
        this->setVisible(LevelEditorLayer::get()->m_playbackMode != PlaybackMode::Playing);

        if (this->isSelected()) {
            m_waitTime += dt;
            if (m_waitTime > 0.25f) {
                m_time -= dt * 1.5f;
                m_timeLabel->setVisible(true);
            }
        }
        else {
            m_time = m_defaultTime;
            m_waitTime = 0;
            m_timeLabel->setVisible(false);
        }

        if (m_time <= 0) {
            this->unselected();
            Brightness::create()->show();
            m_time = m_defaultTime;
        }
        else
            m_timeLabel->setString(CCString::createWithFormat("%.02fs", m_time)->getCString());
    }
};

class $modify(LevelEditorLayer) {
	bool init(GJGameLevel* lvl, bool p1) {
		if (!LevelEditorLayer::init(lvl, p1)) return false;

        auto menu = reinterpret_cast<CCMenu*>(m_editorUI->getChildByID("editor-buttons-menu"));
        if (!menu) {
            auto s = CCDirector::sharedDirector()->getWinSize();

            menu = CCMenu::create();
            menu->registerWithTouchDispatcher();
            menu->setPosition({ s.width - 215, s.height - 192.5f });
            m_editorUI->addChild(menu);
        }

        auto btn = CustomButton::create(CCSprite::create("GJ_editBrightnessBtn_001.png"_spr), m_editorUI, menu_selector(Brightness::onAutomatic));
        btn->setup();
        btn->setID("brightness-button"_spr);
        btn->setPosition({ 80.5f, 30.5f });
        btn->setContentSize({40, 40});
        menu->addChild(btn);

		return true;
	}
};
