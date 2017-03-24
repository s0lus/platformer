#include "Player.h"

Player::Player(AnimationManager &a, Level &lev, int x, int y) : Entity(a, x, y)
{
    option("Player", 0, 100, "stay");
    STATE = stay;
    hit = 0;
    obj = lev.getAllObjects();
}

Player::~Player()
{
    key.clear();
    obj.clear();
}

void Player::keyCheck()
{
    if (key["Left"]) {
        dir = 1;
        if (STATE != duck) {
            dx = -walkSpeed;
        }

        if (STATE == stay) {
            STATE = walk;
        }
    }

    if (key["Right"]) {
        dir = 0;
        if (STATE != duck) {
            dx = walkSpeed;
        }

        if (STATE == stay) {
            STATE = walk;
        }
    }

    if (key["Up"]) {
        if (onLadder) {
            STATE = climb;
        }

        if (STATE == stay || STATE == walk) {
            dy = -jumpBoost;
            STATE = jump;
            animationManager.play("jump");
        }

        if (STATE == swim || STATE == climb) {
            dy = -climbUpSpeed;
        }
    }

    if (key["Down"]) {
        if (STATE == stay || STATE == walk) {
            STATE = duck;
            dx = 0;
        }

        if (STATE == swim || STATE == climb) {
            dy = climbDownSpeed;
        }
    }

    if (key["Space"]) {
        shoot = true;
    }
    
    if (!(key["Right"] || key["Left"])) {
        dx = 0;

        if (STATE == walk) {
            STATE = stay;
        }
    }

    if (!(key["Up"] || key["Down"])) {
        if (STATE == swim || STATE == climb) {
            dy = 0;
        }
    }

    if (!key["Down"]) {
        if (STATE == duck) {
            STATE = stay;
        }
    }

    if (!key["Space"]) {
        shoot = false;
        canShoot = true;
    }
}

void Player::update(float time)
{
    keyCheck();

    if (STATE == stay) {
        animationManager.set("stay");
    }

    if (STATE == walk) {
        animationManager.set("walk");
    }

    if (STATE == jump) {
        animationManager.set("jump");
    }

    if (STATE == duck) {
        animationManager.set("duck");
    }

    if (STATE == climb) {
        animationManager.set("climb");
        animationManager.pause();
        if (dy != 0) {
            animationManager.play();
        }

        if (!onLadder) {
            STATE = stay;
        }
    }

    if ((dy != 0) && (STATE != climb) && (!hit)) {
        STATE = jump;
        animationManager.set("jump");
    }

    if (shoot) {
        if (STATE == walk) {
            shoot = false;
            animationManager.set("shootAndWalk");
            dx = 0;
        }

        if (canShoot) {
            animationManager.set("shoot");
            dx = 0;
        }
        // CanShoot = false;
    }

    if (hit) {
        timer += time;
        if (timer > 1000) {
            hit = false;
            timer = 0;
        }
        animationManager.set("hit");
    }

    if (dir) {
        animationManager.flip();
    }

    x += dx * time;
    collision(0);
    
    if (STATE != climb) {
        dy += g * time;
    }

    y += dy * time;

    onLadder = false;
    collision(1);
    
    if (Health <= 0) {
        key["Right"] = key["Left"] = key["Up"] = key["Down"] = key["Space"] = false;
        animationManager.set("dead");
        dx = 0;
        timer_end += time;

        if (timer_end > 5000) {
            life = false;
        }
    }


    animationManager.tick(time);

    //key["R"] = key["L"] = key["Up"] = key["Down"] = key["Space"] = false;
}

void Player::collision(int num)
{
    for (int i = 0; i < obj.size(); i++) {
        if (getRect().intersects(obj[i].rect)) {
            if (obj[i].name == "wall") {
                if (dy > 0 && num == 1) {
                    y = obj[i].rect.top - h;
                    dy = 0;
                    STATE = stay;
                }

                if (dy < 0 && num == 1) {
                    y = obj[i].rect.top + obj[i].rect.height;
                    dy = 0;
                }

                if (dx > 0 && num == 0) {
                    x = obj[i].rect.left - w;
                }

                if (dx < 0 && num == 0) {
                    x = obj[i].rect.left + obj[i].rect.width;
                }
            }

            if (obj[i].name == "ladder") {
                onLadder = true;
            }

            if (obj[i].name == "SlopeLeft") {
                sf::FloatRect r = obj[i].rect;
                float y0 = (x + w / 2 - r.left) * r.height / r.width + r.top - h;
                if (y > y0)
                    if (x + w / 2 > r.left) {
                        y = y0;
                        dy = 0;
                        STATE = stay;
                    }
            }

            if (obj[i].name == "SlopeRight") {
                sf::FloatRect r = obj[i].rect;
                float y0 = -(x + w / 2 - r.left) * r.height / r.width + r.top + r.height - h;
                if (y > y0) {
                    if (x + w / 2 < r.left + r.width) {
                        y = y0;
                        dy = 0;
                        STATE = stay;
                    }
                }
            }
        }
    }
}