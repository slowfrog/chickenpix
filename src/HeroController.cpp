/* Chickenpix: participation to the Liberated Pixel Cup 2012
 * Copyright (C) 2012 Chickenpix team (see AUTHORS.txt for precise authorship)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#include "log.h"
#include "HeroController.h"
#include "Entity.h"
#include "InputState.h"
#include "Mobile.h"
#include "Resources.h"

void
HeroController::update(EntityManager &em, Entity &entity,
                       const InputState &input, int now) {
  float dx = 0;
  float dy = 0;
  if (input.isKeyDown(InputState::Up)) {
    dy -= 2;
  }
  if (input.isKeyDown(InputState::Down)) {
    dy += 2;
  }
  if (input.isKeyDown(InputState::Left)) {
    dx -= 2;
  }
  if (input.isKeyDown(InputState::Right)) {
    dx += 2;
  }

  Mobile *m = NULL;
  if (!entity.hasComponent(Mobile::TYPE)) {
    m = new Mobile();
    entity.addComponent(m);
  } else {
    m = entity.getComponent<Mobile>();
  }
  m->setSpeed(dx, dy);
}
