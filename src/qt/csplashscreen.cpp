#include <QPainter>
#include "CSplashScreen.h"
 
////////////////////////////////////////////////////////////////////////////
CSplashScreen::CSplashScreen(const QPixmap& thePixmap)
 : QFrame(0, Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint)
 , itsPixmap(thePixmap)
{
 setAttribute(Qt::WA_TranslucentBackground);
 setFixedSize(itsPixmap.size());
};
 
////////////////////////////////////////////////////////////////////////////
void CSplashScreen::clearMessage()
{
 itsMessage.clear();
 repaint();
}

void CSplashScreen::finish(QWidget *mainWin)
{
    if (mainWin) {
#if defined(Q_WS_X11)
        extern void qt_x11_wait_for_window_manager(QWidget *mainWin, bool);
        qt_x11_wait_for_window_manager(mainWin, false);
#endif
    }
    close();
}
  
////////////////////////////////////////////////////////////////////////////
void CSplashScreen::showMessage(const QString& theMessage, int theAlignment/* = Qt::AlignLeft*/, const QColor& theColor/* = Qt::black*/)
{
 itsMessage  = theMessage;
 itsAlignment = theAlignment;
 itsColor  = theColor;
 repaint();
}
 
////////////////////////////////////////////////////////////////////////////
void CSplashScreen::paintEvent(QPaintEvent* pe)
{
 QRect aTextRect(rect());
 aTextRect.setRect(aTextRect.x() + 5, aTextRect.y() + 5, aTextRect.width() - 10, aTextRect.height() - 10);
 
 QPainter aPainter(this);
 aPainter.drawPixmap(rect(), itsPixmap);
 aPainter.setPen(itsColor);
 aPainter.drawText(aTextRect, itsAlignment, itsMessage);
}