#include "draftitemcounter.h"
#include <QtWidgets>

DraftItemCounter::DraftItemCounter(QObject *parent, QHBoxLayout *hLayout, QPixmap pixmap) : QObject(parent)
{
    labelIcon = new HoverLabel();
    labelCounter = new QLabel();
    labelIcon->setPixmap(pixmap.scaledToWidth(32,Qt::SmoothTransformation));
    hLayout->addWidget(labelIcon);
    hLayout->addWidget(labelCounter);

    connect(labelIcon, SIGNAL(enter()),
            this, SLOT(sendIconEnter()));
    connect(labelIcon, SIGNAL(leave()),
            this, SIGNAL(iconLeave()));

    reset();
}


DraftItemCounter::DraftItemCounter(QObject *parent) : QObject(parent)
{
    labelIcon = NULL;
    labelCounter = NULL;
    reset();
}


DraftItemCounter::~DraftItemCounter()
{
    if(labelIcon != NULL)       delete labelIcon;
    if(labelCounter != NULL)    delete labelCounter;
}


void DraftItemCounter::reset()
{
    this->counter = 0;
    this->deckCardList.clear();
    this->deckCardListSyn.clear();

    if(labelIcon != NULL && labelCounter != NULL)
    {
        labelCounter->setText("0");
        labelIcon->setHidden(true);
        labelCounter->setHidden(true);
    }
}


void DraftItemCounter::setTransparency(Transparency transparency, bool mouseInApp)
{
    if(labelIcon != NULL && labelCounter != NULL)
    {
        if(!mouseInApp && transparency == Transparent)
        {
            labelIcon->setStyleSheet("QLabel {background-color: transparent; color: white;}");
            labelCounter->setStyleSheet("QLabel {background-color: transparent; color: white;}");
        }
        else
        {
            labelIcon->setStyleSheet("");
            labelCounter->setStyleSheet("");
        }
    }
}


void DraftItemCounter::increase()
{
    if(labelIcon != NULL && labelCounter != NULL)
    {
        this->counter++;
        labelCounter->setText(QString::number(counter));
        if(counter == 1)
        {
#ifdef QT_DEBUG
            labelIcon->setHidden(false);//TODO Para ocultar los iconos cambiar todos a setHidden(true)
            labelCounter->setHidden(false);//TODO Para ocultar los iconos cambiar todos a setHidden(true)
#endif
        }
    }
}
void DraftItemCounter::increase(int numIncrease, int draftedCardsCount)
{
    if(labelIcon != NULL && labelCounter != NULL)
    {
        if(counter == 0)
        {
#ifdef QT_DEBUG
            labelIcon->setHidden(false);     //TODO Para ocultar los iconos cambiar todos a setHidden(true)
            labelCounter->setHidden(false);  //TODO Para ocultar los iconos cambiar todos a setHidden(true)
#endif
        }
        this->counter += numIncrease;
        labelCounter->setText(QString::number((counter*10/std::max(1,draftedCardsCount))/10.0));
    }
}
void DraftItemCounter::increase(const QString &code, bool count)
{
    bool duplicatedCard = false;
    for(DeckCard &deckCard: deckCardList)
    {
        if(deckCard.getCode() == code)
        {
            deckCard.total++;
            deckCard.remaining = deckCard.total;
            duplicatedCard = true;
            break;
        }
    }

    if(!duplicatedCard)
    {
        deckCardList.append(DeckCard(code));
    }

    if(labelIcon != NULL && labelCounter != NULL && count)
    {
        this->counter++;
        labelCounter->setText(QString::number(counter));
        if(counter == 1)
        {
#ifdef QT_DEBUG
            labelIcon->setHidden(false);     //TODO Para ocultar los iconos cambiar todos a setHidden(true)
            labelCounter->setHidden(false);  //TODO Para ocultar los iconos cambiar todos a setHidden(true)
#endif
        }
    }
}


void DraftItemCounter::increaseSyn(const QString &code)
{
    bool duplicatedCard = false;
    for(DeckCard &deckCard: deckCardListSyn)
    {
        if(deckCard.getCode() == code)
        {
            deckCard.total++;
            deckCard.remaining = deckCard.total;
            duplicatedCard = true;
            break;
        }
    }

    if(!duplicatedCard)
    {
        deckCardListSyn.append(DeckCard(code));
    }
}


bool DraftItemCounter::insertCode(const QString code, QMap<QString,int> &synergies)
{
    for(DeckCard &deckCard: deckCardList)
    {
        if(code == deckCard.getCode())
        {
            if(!synergies.contains(code))
            {
                synergies[code] = deckCard.total;
            }
            return true;
        }
    }
    return false;
}


void DraftItemCounter::insertCards(QMap<QString,int> &synergies)
{
    for(DeckCard &deckCard: deckCardList)
    {
        QString code = deckCard.getCode();
        if(!synergies.contains(code))
        {
            synergies[code] = deckCard.total;
        }
    }
}


void DraftItemCounter::insertSynCards(QMap<QString,int> &synergies)
{
    for(DeckCard &deckCard: deckCardListSyn)
    {
        QString code = deckCard.getCode();
        if(!synergies.contains(code))
        {
            synergies[code] = deckCard.total;
        }
    }
}


bool DraftItemCounter::isEmpty()
{
    return counter == 0;
}


int DraftItemCounter::count()
{
    return counter;
}


void DraftItemCounter::sendIconEnter()
{
    QStringList codes;
    for(DeckCard &deckCard: deckCardList)
    {
        codes.append(deckCard.getCode());
    }

    int labelTop = labelIcon->mapToGlobal(QPoint(0,0)).y();
    int labelBottom = labelIcon->mapToGlobal(QPoint(0,labelIcon->height())).y();

    emit iconEnter(codes, labelTop, labelBottom);
}

