/*
 * OpenRPT report writer and rendering engine
 * Copyright (C) 2001-2007 by OpenMFG, LLC (info@openmfg.com)
 * Copyright (C) 2007-2008 by Adam Pigg (adam@piggz.co.uk)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "KoReportDesignerItemImage.h"
#include <KoReportDesignerItemBase.h>
#include <KoReportDesigner.h>

#include <QImageWriter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QBuffer>
#include <QDomDocument>
#include <QPainter>
#include <kdebug.h>
#include <klocalizedstring.h>

#include <koproperty/Property.h>
#include <koproperty/Set.h>
#include <koproperty/EditorView.h>

//
// ReportEntitiesImage
//
// contructors/deconstructors

void KoReportDesignerItemImage::init(QGraphicsScene * scene)
{
    kDebug();
    if (scene)
        scene->addItem(this);

    KoReportDesignerItemRectBase::init(&m_pos, &m_size, m_set);

    connect(m_set, SIGNAL(propertyChanged(KoProperty::Set&, KoProperty::Property&)),
            this, SLOT(slotPropertyChanged(KoProperty::Set&, KoProperty::Property&)));
	    
    m_controlSource->setListData(m_reportDesigner->fieldKeys(), m_reportDesigner->fieldNames());
    setZValue(Z);
}

KoReportDesignerItemImage::KoReportDesignerItemImage(KoReportDesigner * rw, QGraphicsScene* scene, const QPointF &pos)
        : KoReportDesignerItemRectBase(rw)
{
  kDebug();
    init(scene);
    m_size.setSceneSize(QSizeF(100, 100));
    m_pos.setScenePos(pos);
    m_name->setValue(m_reportDesigner->suggestEntityName("image"));
}

KoReportDesignerItemImage::KoReportDesignerItemImage(QDomNode & element, KoReportDesigner * rw, QGraphicsScene* scene)
        : KoReportItemImage(element), KoReportDesignerItemRectBase(rw)
{
    init(scene);
    setSceneRect(m_pos.toScene(), m_size.toScene());
}

KoReportDesignerItemImage* KoReportDesignerItemImage::clone()
{
    QDomDocument d;
    QDomElement e = d.createElement("clone");;
    QDomNode n;
    buildXML(d, e);
    n = e.firstChild();
    return new KoReportDesignerItemImage(n, designer(), 0);
}

KoReportDesignerItemImage::~KoReportDesignerItemImage()
{
    // do we need to clean anything up?
}

void KoReportDesignerItemImage::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // store any values we plan on changing so we can restore them
    QPen  p = painter->pen();

    if (isInline()) {
        //QImage t_img = _image;
        QImage t_img = m_staticImage->value().value<QPixmap>().toImage();
        if (mode() == "stretch") {
            t_img = t_img.scaled(rect().width(), rect().height(), Qt::KeepAspectRatio);
        }
        painter->drawImage(rect().left(), rect().top(), t_img, 0, 0, rect().width(), rect().height());
    } else {
        painter->drawText(rect(), 0, dataSourceAndObjectTypeName(itemDataSource(), "image"));
    }

    //Draw a border so user knows the object edge
    painter->setPen(QPen(QColor(224, 224, 224)));
    painter->drawRect(rect());


    drawHandles(painter);

    // restore an values before we started just in case
    painter->setPen(p);
}

void KoReportDesignerItemImage::buildXML(QDomDocument & doc, QDomElement & parent)
{
    QDomElement entity = doc.createElement("report:image");

    // properties
    addPropertyAsAttribute(&entity, m_name);
    addPropertyAsAttribute(&entity, m_resizeMode);
    entity.setAttribute("report:z-index", zValue());
    buildXMLRect(doc, entity, &m_pos, &m_size);


    if (isInline()) {
        QDomElement map = doc.createElement("report:inline-image-data");
        map.appendChild(doc.createTextNode(inlineImageData()));
        entity.appendChild(map);
    } else {
        addPropertyAsAttribute(&entity, m_controlSource);
    }

    parent.appendChild(entity);
}

void KoReportDesignerItemImage::slotPropertyChanged(KoProperty::Set &s, KoProperty::Property &p)
{
    if (p.name() == "Name") {
        //For some reason p.oldValue returns an empty string
        if (!m_reportDesigner->isEntityNameUnique(p.value().toString(), this)) {
            p.setValue(m_oldName);
        } else {
            m_oldName = p.value().toString();
        }
    }

    KoReportDesignerItemRectBase::propertyChanged(s, p);
    if (m_reportDesigner) m_reportDesigner->setModified(true);
}

void KoReportDesignerItemImage::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    m_controlSource->setListData(m_reportDesigner->fieldKeys(), m_reportDesigner->fieldNames());
    KoReportDesignerItemRectBase::mousePressEvent(event);
}
