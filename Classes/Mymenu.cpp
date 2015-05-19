#include "Mymenu.h"
#include "base/CCDirector.h"
#include "base/CCTouch.h"
#include "base/CCEventListenerTouch.h"
#include "base/CCEventDispatcher.h"
#include "platform/CCStdC.h"
#include "deprecated/CCString.h"
#include "Gamepanel.h"
#include <vector>

using namespace std;

NS_CC_BEGIN

enum 
{
    kDefaultPadding =  5,
};

//
//CCMenu
//

Mymenu::~Mymenu()
{
    CCLOGINFO("In the destructor of Menu. %p", this);
}


Mymenu* Mymenu::create()
{
    return Mymenu::create(nullptr, nullptr);
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
Menu * Menu::variadicCreate(MenuItem* item, ...)
{
    va_list args;
    va_start(args,item);
    
    Menu *ret = Menu::createWithItems(item, args);
    
    va_end(args);
    
    return ret;
}
#else


Mymenu * Mymenu::create(MenuItem* item, ...)
{
    va_list args;
    va_start(args,item);
    
    Mymenu *ret = Mymenu::createWithItems(item, args);
    
    va_end(args);
    
    return ret;
}
#endif


Mymenu* Mymenu::createWithArray(const Vector<MenuItem*>& arrayOfItems)
{
    auto ret = new (std::nothrow) Mymenu();
    if (ret && ret->initWithArray(arrayOfItems))
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    
    return ret;
}

Mymenu* Mymenu::createWithItems(MenuItem* item, va_list args)
{
    Vector<MenuItem*> items;
    if( item )
    {
        items.pushBack(item);
        MenuItem *i = va_arg(args, MenuItem*);
        while(i)
        {
            items.pushBack(i);
            i = va_arg(args, MenuItem*);
        }
    }
    
    return Mymenu::createWithArray(items);
}

Mymenu* Mymenu::createWithItem(MenuItem* item)
{
    return Mymenu::create(item, nullptr);
}

bool Mymenu::init()
{
    return initWithArray(Vector<MenuItem*>());
}

bool Mymenu::initWithArray(const Vector<MenuItem*>& arrayOfItems)
{
    if (Layer::init())
    {
        _enabled = true;
        // menu in the center of the screen
        Size s = Director::getInstance()->getWinSize();

        this->ignoreAnchorPointForPosition(true);
        setAnchorPoint(Vec2(0.5f, 0.5f));
        this->setContentSize(s);

        setPosition(s.width/2, s.height/2);
        
        int z=0;
        
        for (auto& item : arrayOfItems)
        {
            this->addChild(item, z);
            z++;
        }
    
        _selectedItem = nullptr;
        _state = Mymenu::State::WAITING;
        
        // enable cascade color and opacity on menus
        setCascadeColorEnabled(true);
        setCascadeOpacityEnabled(true);
        
        
        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->setSwallowTouches(false);//改为false不会像下传递
        
        touchListener->onTouchBegan = CC_CALLBACK_2(Mymenu::onTouchBegan, this);
        touchListener->onTouchMoved = CC_CALLBACK_2(Mymenu::onTouchMoved, this);
        touchListener->onTouchEnded = CC_CALLBACK_2(Mymenu::onTouchEnded, this);
        touchListener->onTouchCancelled = CC_CALLBACK_2(Mymenu::onTouchCancelled, this);
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
        
        return true;
    }
    return false;
}

/*
* override add:
*/
void Mymenu::addChild(Node * child)
{
    Layer::addChild(child);
}

void Mymenu::addChild(Node * child, int zOrder)
{
    Layer::addChild(child, zOrder);
}

void Mymenu::addChild(Node * child, int zOrder, int tag)
{
    CCASSERT( dynamic_cast<MenuItem*>(child) != nullptr, "Menu only supports MenuItem objects as children");
    Layer::addChild(child, zOrder, tag);
}

void Mymenu::addChild(Node * child, int zOrder, const std::string &name)
{
    CCASSERT( dynamic_cast<MenuItem*>(child) != nullptr, "Menu only supports MenuItem objects as children");
    Layer::addChild(child, zOrder, name);
}

void Mymenu::onEnter()
{
    Layer::onEnter();
}

void Mymenu::onExit()
{
    if (_state == Mymenu::State::TRACKING_TOUCH)
    {
        if (_selectedItem)
        {
            _selectedItem->unselected();
            _selectedItem = nullptr;
        }
        
        _state = Mymenu::State::WAITING;
    }

    Layer::onExit();
}

void Mymenu::removeChild(Node* child, bool cleanup)
{
    MenuItem *menuItem = dynamic_cast<MenuItem*>(child);
    CCASSERT(menuItem != nullptr, "Menu only supports MenuItem objects as children");
    
    if (_selectedItem == menuItem)
    {
        _selectedItem = nullptr;
    }
    
    Node::removeChild(child, cleanup);
}

//Menu - Events

bool Mymenu::onTouchBegan(Touch* touch, Event* event)
{
    if (_state != Mymenu::State::WAITING || ! _visible || !_enabled)
    {
        return false;
    }
    
    for (Node *c = this->_parent; c != nullptr; c = c->getParent())
    {
        if (c->isVisible() == false)
        {
            return false;
        }
    }
    
    _selectedItem = this->getItemForTouch(touch);
    if (_selectedItem)
    {
        _state = Mymenu::State::TRACKING_TOUCH;
        _selectedItem->selected();
		thepoint=convertToWorldSpace(_selectedItem->getPosition());
        return true;
    }
    
	

    return false;
}

void Mymenu::onTouchEnded(Touch* touch, Event* event)
{
    CCASSERT(_state == Mymenu::State::TRACKING_TOUCH, "[Menu ccTouchEnded] -- invalid state");
    this->retain();
    if (_selectedItem)
    {
        _selectedItem->unselected();
		if(thepoint==convertToWorldSpace(_selectedItem->getPosition()))
			if(convertToWorldSpace(_selectedItem->getPosition()).y<1054*Gamepanel::scaleFactory&&convertToWorldSpace(_selectedItem->getPosition()).y>162*Gamepanel::scaleFactory)
        _selectedItem->activate();
    }
    _state = Mymenu::State::WAITING;
    this->release();
}

void Mymenu::onTouchCancelled(Touch* touch, Event* event)
{
    CCASSERT(_state == Mymenu::State::TRACKING_TOUCH, "[Menu ccTouchCancelled] -- invalid state");
    this->retain();
    if (_selectedItem)
    {
        _selectedItem->unselected();
    }
    _state = Mymenu::State::WAITING;
    this->release();
}

void Mymenu::onTouchMoved(Touch* touch, Event* event)
{
    CCASSERT(_state == Mymenu::State::TRACKING_TOUCH, "[Menu ccTouchMoved] -- invalid state");
    MenuItem *currentItem = this->getItemForTouch(touch);
    if (currentItem != _selectedItem)
    {
        if (_selectedItem)
        {
            _selectedItem->unselected();
        }
        _selectedItem = currentItem;
        if (_selectedItem)
        {
            _selectedItem->selected();
        }
    }
}

//Menu - Alignment
void Mymenu::alignItemsVertically()
{
    this->alignItemsVerticallyWithPadding(kDefaultPadding);
}

void Mymenu::alignItemsVerticallyWithPadding(float padding)
{
    float height = -padding;

    for(const auto &child : _children)
        height += child->getContentSize().height * child->getScaleY() + padding;

    float y = height / 2.0f;
    
    for(const auto &child : _children) {
        child->setPosition(0, y - child->getContentSize().height * child->getScaleY() / 2.0f);
        y -= child->getContentSize().height * child->getScaleY() + padding;
    }
}

void Mymenu::alignItemsHorizontally(void)
{
    this->alignItemsHorizontallyWithPadding(kDefaultPadding);
}

void Mymenu::alignItemsHorizontallyWithPadding(float padding)
{
    float width = -padding;
    for(const auto &child : _children)
        width += child->getContentSize().width * child->getScaleX() + padding;

    float x = -width / 2.0f;
    
    for(const auto &child : _children) {
        child->setPosition(x + child->getContentSize().width * child->getScaleX() / 2.0f, 0);
        x += child->getContentSize().width * child->getScaleX() + padding;
    }
}

void Mymenu::alignItemsInColumns(int columns, ...)
{
    va_list args;
    va_start(args, columns);

    this->alignItemsInColumns(columns, args);

    va_end(args);
}

void Mymenu::alignItemsInColumns(int columns, va_list args)
{
    CCASSERT(columns >= 0, "Columns must be >= 0");
    ValueVector rows;
    while (columns)
    {
        rows.push_back(Value(columns));
        columns = va_arg(args, int);
    }
    alignItemsInColumnsWithArray(rows);
}

void Mymenu::alignItemsInColumnsWithArray(const ValueVector& rows)
{
    int height = -5;
    size_t row = 0;
    int rowHeight = 0;
    int columnsOccupied = 0;
    int rowColumns = 0;

    for(const auto &child : _children) {
        CCASSERT(row < rows.size(), "");
        
        rowColumns = rows[row].asInt();
        // can not have zero columns on a row
        CCASSERT(rowColumns, "");
        
        float tmp = child->getContentSize().height;
        rowHeight = (unsigned int)((rowHeight >= tmp || isnan(tmp)) ? rowHeight : tmp);
        
        ++columnsOccupied;
        if (columnsOccupied >= rowColumns)
        {
            height += rowHeight + 5;
            
            columnsOccupied = 0;
            rowHeight = 0;
            ++row;
        }
    }

    // check if too many rows/columns for available menu items
    CCASSERT(! columnsOccupied, "");

    Size winSize = Director::getInstance()->getWinSize();

    row = 0;
    rowHeight = 0;
    rowColumns = 0;
    float w = 0.0;
    float x = 0.0;
    float y = (float)(height / 2);

    for(const auto &child : _children) {
        if (rowColumns == 0)
        {
            rowColumns = rows[row].asInt();
            w = winSize.width / (1 + rowColumns);
            x = w;
        }

        float tmp = child->getContentSize().height;
        rowHeight = (unsigned int)((rowHeight >= tmp || isnan(tmp)) ? rowHeight : tmp);

        child->setPosition(x - winSize.width / 2,
                               y - child->getContentSize().height / 2);

        x += w;
        ++columnsOccupied;

        if (columnsOccupied >= rowColumns)
        {
            y -= rowHeight + 5;

            columnsOccupied = 0;
            rowColumns = 0;
            rowHeight = 0;
            ++row;
        }
    }
}

void Mymenu::alignItemsInRows(int rows, ...)
{
    va_list args;
    va_start(args, rows);

    this->alignItemsInRows(rows, args);

    va_end(args);
}

void Mymenu::alignItemsInRows(int rows, va_list args)
{
    ValueVector array;
    while (rows)
    {
        array.push_back(Value(rows));
        rows = va_arg(args, int);
    }
    alignItemsInRowsWithArray(array);
}

void Mymenu::alignItemsInRowsWithArray(const ValueVector& columns)
{
    vector<int> columnWidths;
    vector<int> columnHeights;

    int width = -10;
    int columnHeight = -5;
    size_t column = 0;
    int columnWidth = 0;
    int rowsOccupied = 0;
    int columnRows;

    for(const auto &child : _children) {
        // check if too many menu items for the amount of rows/columns
        CCASSERT(column < columns.size(), "");

        columnRows = columns[column].asInt();
        // can't have zero rows on a column
        CCASSERT(columnRows, "");

        // columnWidth = fmaxf(columnWidth, [item contentSize].width);
        float tmp = child->getContentSize().width;
        columnWidth = (unsigned int)((columnWidth >= tmp || isnan(tmp)) ? columnWidth : tmp);

        columnHeight += (int)(child->getContentSize().height + 5);
        ++rowsOccupied;

        if (rowsOccupied >= columnRows)
        {
            columnWidths.push_back(columnWidth);
            columnHeights.push_back(columnHeight);
            width += columnWidth + 10;

            rowsOccupied = 0;
            columnWidth = 0;
            columnHeight = -5;
            ++column;
        }
    }

    // check if too many rows/columns for available menu items.
    CCASSERT(! rowsOccupied, "");

    Size winSize = Director::getInstance()->getWinSize();

    column = 0;
    columnWidth = 0;
    columnRows = 0;
    float x = (float)(-width / 2);
    float y = 0.0;

    for(const auto &child : _children) {
        if (columnRows == 0)
        {
            columnRows = columns[column].asInt();
            y = (float) columnHeights[column];
        }

        // columnWidth = fmaxf(columnWidth, [item contentSize].width);
        float tmp = child->getContentSize().width;
        columnWidth = (unsigned int)((columnWidth >= tmp || isnan(tmp)) ? columnWidth : tmp);

        child->setPosition(x + columnWidths[column] / 2,
                               y - winSize.height / 2);

        y -= child->getContentSize().height + 10;
        ++rowsOccupied;

        if (rowsOccupied >= columnRows)
        {
            x += columnWidth + 5;
            rowsOccupied = 0;
            columnRows = 0;
            columnWidth = 0;
            ++column;
        }
    }
}

MenuItem* Mymenu::getItemForTouch(Touch *touch)
{
    Vec2 touchLocation = touch->getLocation();

    if (!_children.empty())
    {
        for (auto iter = _children.crbegin(); iter != _children.crend(); ++iter)
        {
            MenuItem* child = dynamic_cast<MenuItem*>(*iter);
            if (child && child->isVisible() && child->isEnabled())
            {
                Vec2 local = child->convertToNodeSpace(touchLocation);
                Rect r = child->rect();
                r.origin = Vec2::ZERO;
                
                if (r.containsPoint(local))
                {
                    return child;
                }
            }
        }
    }

    return nullptr;
}

std::string Mymenu::getDescription() const
{
    return StringUtils::format("<Menu | Tag = %d>", _tag);
}

NS_CC_END
