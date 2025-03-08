#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EditorUI.hpp>


class $modify(EditorUIHook, EditorUI) {
	struct Fields {
		CCSprite* m_filterIndicatorIcon;
		CCSprite* m_filterIndicatorObj;
	};

	void updateFilterIndicator(float bruh) {

		CCSprite* filterIndicatorIcon = m_fields->m_filterIndicatorIcon;
		CCSprite* filterIndicatorObj = m_fields->m_filterIndicatorObj;

		int filterType = GameManager::get()->getIntGameVariable("0005");
		if (filterType != 3) {
			filterIndicatorIcon->setVisible(false);
			filterIndicatorObj->setVisible(false);
			return;
		}

		int objectID = GameManager::get()->getIntGameVariable("0006");
		if (filterIndicatorIcon && objectID >= 0) {

			const char* fileName = ObjectToolbox::sharedState()->intKeyToFrame(objectID);
			filterIndicatorObj->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fileName));

			filterIndicatorIcon->setVisible(true);
			filterIndicatorObj->setVisible(true);

			// CCSize contentSize = filterIndicatorObj->getContentSize();
			// filterIndicatorObj->setScale(10 / contentSize.height);
			
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

		this->schedule(schedule_selector(EditorUIHook::updateFilterIndicator), 0.05f);
	}
};