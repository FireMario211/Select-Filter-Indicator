#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EditorUI.hpp>


class $modify(EditorUIHook, EditorUI) {
	struct Fields {
		CCSprite* m_filterIndicatorIcon;
		CCSprite* m_filterIndicatorObj;
	};

	void updateFilterIndicator() {

		CCSprite* filterIndicatorIcon = m_fields->m_filterIndicatorIcon;
		CCSprite* filterIndicatorObj = m_fields->m_filterIndicatorObj;

		int filterType = GameManager::get()->getIntGameVariable("0005");

		switch (filterType) {
			case 1:
				filterIndicatorIcon->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("deleteFilter_details_001.png"));
				filterIndicatorIcon->setVisible(true);
				filterIndicatorObj->setVisible(false);
				break;

			case 2:
				filterIndicatorIcon->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("deleteFilter_static_001.png"));
				filterIndicatorIcon->setVisible(true);
				filterIndicatorObj->setVisible(false);
				break;

			case 3:
			{
				int objectID = GameManager::get()->getIntGameVariable("0006");
				if (filterIndicatorIcon && objectID >= 0) {
					const char* fileName = ObjectToolbox::sharedState()->intKeyToFrame(objectID);
					filterIndicatorIcon->setVisible(true);
					filterIndicatorObj->setVisible(true);

					filterIndicatorObj->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fileName));
					filterIndicatorIcon->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("deleteFilter_custom_001.png"));
				}
				break;
			}

			default:
				filterIndicatorIcon->setVisible(false);
				filterIndicatorObj->setVisible(false);
				break;
		}
	}

	bool init(LevelEditorLayer* editorLayer) {
		if (!EditorUI::init(editorLayer)) {
			return false;
		}

		CCSprite* deleteButton = (CCSprite*)getChildByIDRecursive("delete-trash-button");
		CCSprite* filterIndicatorIcon = CCSprite::createWithSpriteFrameName("deleteFilter_custom_001.png");
		deleteButton->addChild(filterIndicatorIcon);
		filterIndicatorIcon->setPosition(CCPoint(30, 10));

		CCSprite* filterIndicatorObj = CCSprite::create();
		filterIndicatorObj->setParent(filterIndicatorIcon);
		filterIndicatorIcon->addChild(filterIndicatorObj);
		filterIndicatorObj->setPosition(CCPoint(13.75f, 9.0f));
		filterIndicatorObj->setScale(0.33f);

		filterIndicatorIcon->setZOrder(1);
		filterIndicatorObj->setZOrder(-1);

		m_fields->m_filterIndicatorIcon = filterIndicatorIcon;
		m_fields->m_filterIndicatorObj = filterIndicatorObj;

		updateFilterIndicator();

		deleteButton->updateDisplayedOpacity(deleteButton->getOpacity());

		return true;
	}

	void onUpdateDeleteFilter(cocos2d::CCObject* sender) {
		EditorUI::onUpdateDeleteFilter(sender);
		updateFilterIndicator();
	}
	
};