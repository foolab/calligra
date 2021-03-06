/*
 *  Copyright (c) 2011 Dmitry Kazakov <dimula73@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef __KIS_MODEL_INDEX_CONVERTER_TEST_H
#define __KIS_MODEL_INDEX_CONVERTER_TEST_H

#include <QtTest/QtTest>

#include "empty_nodes_test.h"

class KisDummiesFacadeBase;
class KisNodeModel;
class KisModelIndexConverterBase;


class KisModelIndexConverterTest : public QObject, public TestUtil::EmptyNodesTest
{
    Q_OBJECT
private slots:
    void init();
    void cleanup();

    void testIndexFromDummy();
    void testIndexFromAddedAllowedDummy();
    void testIndexFromAddedDeniedDummy();
    void testDummyFromRow();
    void testRowCount();

    void testIndexFromDummyShowAll();
    void testIndexFromAddedAllowedDummyShowAll();
    void testIndexFromAddedDeniedDummyShowAll();
    void testDummyFromRowShowAll();
    void testRowCountShowAll();

private:
    inline void checkIndexFromDummy(KisNodeSP node, int row);
    inline void checkInvalidIndexFromDummy(KisNodeSP node);
    inline void checkIndexFromAddedAllowedDummy(KisNodeSP parent, int index, int parentRow, int childRow, bool parentValid);
    inline void checkIndexFromAddedDeniedDummy(KisNodeSP parent, int index, int parentRow, int childRow, bool parentValid);
    inline void checkIndexFromAddedDummy(KisNodeSP parent, int index, const QString &type, int parentRow, int childRow, bool parentValid);
    inline void checkInvalidIndexFromAddedAllowedDummy(KisNodeSP parent, int index);
    inline void checkInvalidIndexFromAddedDeniedDummy(KisNodeSP parent, int index);
    inline void checkInvalidIndexFromAddedDummy(KisNodeSP parent, int index, const QString &type);
    inline void checkDummyFromRow(KisNodeSP parent, int row, KisNodeSP expectedNode);
    inline void checkRowCount(KisNodeSP parent, int rowCount);

private:
    KisDummiesFacadeBase *m_dummiesFacade;
    KisNodeModel *m_nodeModel;
    KisModelIndexConverterBase *m_indexConverter;
};

#endif /* __KIS_MODEL_INDEX_CONVERTER_TEST_H */
