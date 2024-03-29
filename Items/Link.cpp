#include "Link.h"
namespace Uber {
    Point::Point(QPointF p)
    :QObject(nullptr)
    ,m_Point(p)
    {

    }

    QPointF Point::get() const
    {
        return m_Point;
    }

    void Point::set( const QPointF &p )
    {
        m_Point = p;
    }

    qreal Point::getX() const
    {
        return m_Point.x();
    }

    void Point::setX( const qreal &x )
    {
        m_Point.setX(x);
    }

    qreal Point::getY() const
    {
        return m_Point.y();
    }

    void Point::setY( const qreal &y )
    {
        m_Point.setY(y);
    }

    Link::Link()
    :m_Inlet( new Inlet() )
    ,m_Outlet( new Outlet() )
    {
        QObject::connect(m_Inlet, SIGNAL(positionChanged()),this, SIGNAL(linkChanged()));
        QObject::connect(m_Outlet, SIGNAL(positionChanged()),this, SIGNAL(linkChanged()));
    }
    void Link::setInlet( Inlet *inlet )
    {
        delete m_Inlet;
        m_Inlet = inlet;
        QObject::connect(m_Inlet, SIGNAL(positionChanged()),this, SIGNAL(linkChanged()));
        emit positionChanged();
    }

    void Link::setOutlet( Outlet *outlet )
    {
        delete m_Outlet;
        m_Outlet = outlet;
        QObject::connect(m_Outlet, SIGNAL(positionChanged()),this, SIGNAL(linkChanged()));
        emit positionChanged();
    }

    void Link::addPoint( const QPointF &p )
    {
        m_Points.push_back(new Point(p) );
    }

    QObjectList Link::getPoints()
    {
        return m_Points;
    }
    /*
     * A link always starts from an outlet and ends at an inlet.
     * This is not affected by the way a connection is made.
     */
    QPointF Link::getStartPos()
    {
        if ( m_Outlet )
        {
            return m_Outlet->getPosition();
        } else
        {
            return QPointF(0,0);
        }
    }

    QPointF Link::getEndPos()
    {
        if ( m_Inlet )
        {
            return m_Inlet->getPosition();
        } else
        {
            return QPointF(0,0);
        }
    }

    void Link::updatePosition( const QPointF& pos )
    {
        if ( m_Inlet->isValid() && m_Outlet->isValid() )
            return;
        if ( !m_Inlet->isValid() )
        {
            m_Inlet->setPosition(pos);
            qDebug() << "Updated inlet position to: " << pos;
        } else if ( !m_Outlet->isValid() )
        {
            m_Outlet->setPosition(pos);
            qDebug() << "Updated outlet position to: " << pos ;
        }
    }

    QDebug operator<<(QDebug dbg, const Link &link )
    {
        Q_UNUSED(link)
        dbg.nospace() << "Link";
        return dbg.maybeSpace();
    }
}
