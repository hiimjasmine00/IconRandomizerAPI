#include <Geode/binding/GameManager.hpp>
#include <Geode/binding/SimplePlayer.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <hiimjustin000.more_icons/include/MoreIcons.hpp>
#include <IconRandomizer.hpp>

using namespace geode::prelude;

class $modify(MyGarageLayer, GJGarageLayer) {
    bool init() {
        if (!GJGarageLayer::init()) return false;

        auto menu = getChildByID("shards-menu");
        auto myButton = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_likeBtn_001.png"),
            this,
            menu_selector(MyGarageLayer::onMyButton)
        );
        myButton->setID("my-button"_spr);
        menu->addChild(myButton);
        menu->updateLayout();

        return true;
    }

    void onMyButton(CCObject*) {
        IconRandomizer::init();
        auto randomType = (IconType)IconRandomizer::random(0, 8);
        IconRandomizer::randomize(IconRandomizer::fromIconType(randomType));
        IconRandomizer::randomize(IconRandomizer::fromIconType(randomType), true);
        auto customIcon = MoreIcons::activeForType(randomType);
        if (!customIcon.empty()) MoreIcons::updateSimplePlayer(m_playerObject, customIcon, randomType);
        else m_playerObject->updatePlayerFrame(GameManager::get()->activeIconForType(randomType), randomType);
    }
};
