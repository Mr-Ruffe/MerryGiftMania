#include "GiftCounter.h"
#include "Present.h"
#include "Timer.h"
#include <vector>

GiftCounter::GiftCounter(Label *labelRef)
    : Sprite(labelRef->getRect().x + 90, labelRef->getRect().y + 40, 50, 50, constants::gResPath + "images/present2.png"),
      amountOfPresents(0),
      label(labelRef)
{
}

void GiftCounter::tick()
{
    if (amountOfPresents == 0)
    {
        amountOfPresents = countCurrentPresents();
        updateCount();
    }
    for (auto &component : ses.getComponentsOfType(typeid(GiftCounter)))
    {
        GiftCounter *giftCounter = dynamic_cast<GiftCounter *>(component);
        giftCounter->updateCount();
    }
}

int GiftCounter::countCurrentPresents() const
{
    return ses.getComponentsOfType(typeid(Present)).size();
}

void GiftCounter::updateCount()
{
    int count = countCurrentPresents();
    std::string labelString = std::to_string(amountOfPresents - count) + "/" + std::to_string(amountOfPresents);
    label->setText(labelString);
    if (count == 0)
    {
        for (auto &component : ses.getComponentsOfType(typeid(Timer)))
        {
            Timer *timer = dynamic_cast<Timer *>(component);
            timer->gameWon();
        }
    }
}