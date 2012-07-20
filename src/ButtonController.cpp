#include "log.h"
#include "ButtonController.h"
#include "EntityManager.h"
#include "InputState.h"
#include "BVisual.h"
#include "Camera.h"
#include "Transform.h"
#include "Collider.h"
#include "Actionable.h"

const string &ButtonController::ButtonJustDown("ButtonJustDown");
const string &ButtonController::ButtonDown("ButtonDown");
const string &ButtonController::ButtonClicked("ButtonClicked");

void
ButtonController::update(EntityManager &em, Entity &entity,
                         const InputState &input, int now) {
  if (!entity.hasComponent(Transform::TYPE)) {
    LOG2 << "Missing Transform component for ButtonController.\n";
    return;
  }
  const Transform *trans = entity.getComponent<Transform>();

  const BVisual *visu = NULL;
  const Collider *collider = NULL;
  if (entity.hasComponent(Collider::TYPE)) {
    collider = entity.getComponent<Collider>();
  }
  if (entity.hasComponent(BVisual::TYPE)) {
    visu = entity.getComponent<BVisual>();
  }
  if ((collider == NULL) && (visu == NULL)) {
    LOG2 << "Missing Collider or BVisual component for ButtonController.\n";
    return;
  }

  Actionable *actionable = NULL;
  if (!entity.hasComponent(Actionable::TYPE)) {
    actionable = new Actionable();
    entity.addComponent(actionable);
  } else {
    actionable = entity.getComponent<Actionable>();
  }
  
  float minX = trans->getX();
  float minY = trans->getY();
  if ((visu != NULL) && (!visu->isGUI())) {
    const Entity *cameraEntity = em.getFirst(Camera::TYPE);
    if (cameraEntity) {
      if (cameraEntity->hasComponent(Transform::TYPE)) {
        const Transform *camtrans = cameraEntity->getComponent<Transform>();
        const Camera *camera = cameraEntity->getComponent<Camera>();
        minX -= (camtrans->getX() +
                 camera->getOffsetX() - camera->getWidth() / 2);
        minY -= (camtrans->getY() +
                 camera->getOffsetY() - camera->getHeight() / 2);
      } else {
        LOG2 << "Camera entity has no Transform\n";
      }
    }
  }

  if (collider != NULL) {
    minX -= collider->getLeft();
    minY -= collider->getTop();
  } else {
    minX -= visu->getCenterX();
    minY -= visu->getCenterY();
  }

  float maxX = minX;
  float maxY = minY;
  if (collider != NULL) {
    maxX += collider->getLeft() + collider->getRight();
    maxY += collider->getTop() + collider->getBottom();
  } else {
    VisualContext &vc = input.getVisualContext();
    maxX += visu->getWidth(vc);
    maxY += visu->getHeight(vc);
  }
  
  InputState::MousePos mpos = input.getMousePosition();
  const string &prevAction = actionable->getAction();
  const string *action = NULL;
  if ((mpos.x >= minX) && (mpos.x <= maxX) &&
      (mpos.y >= minY) && (mpos.y <= maxY)) {
    // Mouse is over button
    if (input.isButtonDown(InputState::LeftButton)) {
      // and left mouse button is down
      if ((prevAction == ButtonJustDown) || (prevAction == ButtonDown)) {
        action = &ButtonDown;
      } else {
        action = &ButtonJustDown;
      }

    } else if ((prevAction == ButtonJustDown) || (prevAction == ButtonDown)) {
      // mouse button is released over the entity but was previouly down:
      // it's a click
      action = &ButtonClicked;
    }
  }
  
  if (action != NULL) {
    actionable->setAction(*action);
  } else {
    actionable->clearAction();
  }
  
}
