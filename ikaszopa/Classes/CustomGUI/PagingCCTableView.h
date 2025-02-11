/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2010 Sangwoo Im
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __PAGINGCCTABLEVIEW_H__
#define __PAGINGCCTABLEVIEW_H__

#include "./PagingCCScrollView.h"
#include "./PagingCCTableViewCell.h"

#include "cocos2d.h"
using namespace cocos2d;

#include <set>
#include <vector>

class PagingTableView;
/**
 * Sole purpose of this delegate is to single touch event in this version.
 */
class PagingTableViewDelegate : public PagingScrollViewDelegate
{
public:
    /**
     * Delegate to respond touch event
     *
     * @param table table contains the given cell
     * @param cell  cell that is touched
     * @js NA
     * @lua NA
     */
    virtual void tableCellTouched(PagingTableView* table, PagingTableViewCell* cell) = 0;
    
    /**
     * Delegate to respond a table cell press event.
     *
     * @param table table contains the given cell
     * @param cell  cell that is pressed
     * @js NA
     * @lua NA
     */
    virtual void tableCellHighlight(PagingTableView* table, PagingTableViewCell* cell){};
    
    /**
     * Delegate to respond a table cell release event
     *
     * @param table table contains the given cell
     * @param cell  cell that is pressed
     * @js NA
     * @lua NA
     */
    virtual void tableCellUnhighlight(PagingTableView* table, PagingTableViewCell* cell){};
    
    /**
     * Delegate called when the cell is about to be recycled. Immediately
     * after this call the cell will be removed from the scene graph and
     * recycled.
     *
     * @param table table contains the given cell
     * @param cell  cell that is pressed
     * @js NA
     * @lua NA
     */
    virtual void tableCellWillRecycle(PagingTableView* table, PagingTableViewCell* cell){};
    
};


/**
 * Data source that governs table backend data.
 */
class PagingTableViewDataSource
{
public:
    /**
     * @js NA
     * @lua NA
     */
    virtual ~PagingTableViewDataSource() {}
    
    /**
     * cell size for a given index
     *
     * @param idx the index of a cell to get a size
     * @return size of a cell at given index
     */
    virtual Size tableCellSizeForIndex(PagingTableView *table, ssize_t idx) {
        return cellSizeForTable(table);
    };
    /**
     * cell height for a given table.
     *
     * @param table table to hold the instances of Class
     * @return cell size
     */
    virtual Size cellSizeForTable(PagingTableView *table) {
        return Size::ZERO;
    };
    /**
     * a cell instance at a given index
     *
     * @param idx index to search for a cell
     * @return cell found at idx
     */
    virtual PagingTableViewCell* tableCellAtIndex(PagingTableView *table, ssize_t idx) = 0;
    /**
     * Returns number of cells in a given table view.
     *
     * @return number of cells
     */
    virtual ssize_t numberOfCellsInTableView(PagingTableView *table) = 0;
    
};


/**
 * UITableView support for cocos2d-x.
 *
 * This is a very basic, minimal implementation to bring UITableView-like component into cocos2d world.
 */
class PagingTableView : public PagingScrollView, public PagingScrollViewDelegate
{
public:
    
    enum class VerticalFillOrder
    {
        TOP_DOWN,
        BOTTOM_UP
    };
    
    /** Empty contructor of PagingTableView */
    static PagingTableView* create();
    
    /**
     * An intialized table view object
     *
     * @param dataSource data source
     * @param size view size
     * @return table view
     * @code
     * when this function bound to js or lua,the input params are changed
     * in js:var create(var jsObject,var size)
     * in lua:local create(var size)
     * in lua:
     * @endcode
     */
    static PagingTableView* create(PagingTableViewDataSource* dataSource, Size size);
    /**
     * An initialized table view object
     *
     * @param dataSource data source;
     * @param size view size
     * @param container parent object for cells
     * @return table view
     * @code
     * when this function bound to js or lua,the input params are changed
     * in js:var create(var jsObject,var size,var container)
     * in lua:local create(var size, var container)
     * in lua:
     * @endcode
     */
    static PagingTableView* create(PagingTableViewDataSource* dataSource, Size size, Node *container);
    /**
     * @js ctor
     */
    PagingTableView();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~PagingTableView();
    
    bool initWithViewSize(Size size, Node* container = NULL);
    
    /**
     * data source
     * @js NA
     * @lua NA
     */
    PagingTableViewDataSource* getDataSource() { return _dataSource; }
    /**
     * when this function bound to js or lua,the input params are changed
     * in js:var setDataSource(var jsSource)
     * in lua:local setDataSource()
     * @endcode
     */
    void setDataSource(PagingTableViewDataSource* source) { _dataSource = source; }
    /**
     * delegate
     * @js NA
     * @lua NA
     */
    PagingTableViewDelegate* getDelegate() { return _tableViewDelegate; }
    /**
     * @code
     * when this function bound to js or lua,the input params are changed
     * in js:var setDelegate(var jsDelegate)
     * in lua:local setDelegate()
     * @endcode
     */
    void setDelegate(PagingTableViewDelegate* pDelegate) { _tableViewDelegate = pDelegate; }
    
    /**
     * determines how cell is ordered and filled in the view.
     */
    void setVerticalFillOrder(VerticalFillOrder order);
    VerticalFillOrder getVerticalFillOrder();
    
    /**
     * Updates the content of the cell at a given index.
     *
     * @param idx index to find a cell
     */
    void updateCellAtIndex(ssize_t idx);
    /**
     * Inserts a new cell at a given index
     *
     * @param idx location to insert
     */
    void insertCellAtIndex(ssize_t idx);
    /**
     * Removes a cell at a given index
     *
     * @param idx index to find a cell
     */
    void removeCellAtIndex(ssize_t idx);
    /**
     * reloads data from data source.  the view will be refreshed.
     */
    void reloadData();
    /**
     * Dequeues a free cell if available. nil if not.
     *
     * @return free cell
     */
    PagingTableViewCell *dequeueCell();
    
    /**
     * Returns an existing cell at a given index. Returns nil if a cell is nonexistent at the moment of query.
     *
     * @param idx index
     * @return a cell at a given index
     */
    PagingTableViewCell *cellAtIndex(ssize_t idx);
    
    // Overrides
    virtual void scrollViewDidScroll(PagingScrollView* view) override;
    virtual void scrollViewDidZoom(PagingScrollView* view)  override {}
    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent) override;
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent) override;
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent) override;
    virtual void onTouchCancelled(Touch *pTouch, Event *pEvent) override;
    
protected:
    long __indexFromOffset(Vec2 offset);
    long _indexFromOffset(Vec2 offset);
    Vec2 __offsetFromIndex(ssize_t index);
    Vec2 _offsetFromIndex(ssize_t index);
    
    void _moveCellOutOfSight(PagingTableViewCell *cell);
    void _setIndexForCell(ssize_t index, PagingTableViewCell *cell);
    void _addCellIfNecessary(PagingTableViewCell * cell);
    
    void _updateCellPositions();
    
    
    PagingTableViewCell *_touchedCell;
    /**
     * vertical direction of cell filling
     */
    VerticalFillOrder _vordering;
    
    /**
     * index set to query the indexes of the cells used.
     */
    std::set<ssize_t>* _indices;
    
    /**
     * vector with all cell positions
     */
    std::vector<float> _vCellsPositions;
    //NSMutableIndexSet *indices_;
    /**
     * cells that are currently in the table
     */
    Vector<PagingTableViewCell*> _cellsUsed;
    /**
     * free list of cells
     */
    Vector<PagingTableViewCell*> _cellsFreed;
    /**
     * weak link to the data source object
     */
    PagingTableViewDataSource* _dataSource;
    /**
     * weak link to the delegate object
     */
    PagingTableViewDelegate* _tableViewDelegate;
    
    Direction _oldDirection;
    
    bool _isUsedCellsDirty;
    
public:
    void _updateContentSize();
    
};


#endif /* __PAGINGCCTABLEVIEW_H__ */
