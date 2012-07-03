#include "log.h"
#include "ButtonController.h"
#include "EntityManager.h"
#include "InputState.h"
#include "BVisual.h"
#include "Camera.h"
#include "Transform.h"

void
ButtonController::update(EntityManager &em, Entity &entity,
                         const InputState &input, int now) {
  if (!entity.hasComponent(Transform::TYPE)) {
    LOG2 << "Missing Transform component for ButtonController.\n";
    return;
  }
  const Transform *trans = entity.getComponent<Transform>();
  if (!entity.hasComponent(BVisual::TYPE)) {
    LOG2 << "Missing BVisual component for ButtonController.\n";
    return;
  }
  const BVisual *visu = entity.getComponent<BVisual>();

  float minX = trans->getX();
  float minY = trans->getY();
  if (!visu->isGUI()) {
    const Entity *cameraEntity = em.getEntity(Camera::TYPE);
    if (cameraEntity) {
      const Camera *camera = cameraEntity->getComponent<Camera>();
      minX -= camera->getOffsetX();
      minY -= camera->getOffsetY();
    }
  }

  VisualContext &vc = input.getVisualContext();
  float maxX = minX + visu->getWidth(vc);
  float maxY = minY + visu->getHeight(vc);
  InputState::MousePos mpos = input.getMousePosition();
  if ((mpos.x >= minX) && (mpos.x <= maxX) &&
      (mpos.y >= minY) && (mpos.y <= maxY)) {
    // Mouse is over button
    if (input.isButtonDown(InputState::LeftButton)) {
      LOG2 << "Button clicked\n";
      // button is pressed
    } else {
      // button is not pressed
    }
  }
  
}
