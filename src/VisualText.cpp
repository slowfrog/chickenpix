#include "VisualText.h"

VisualText::VisualText(const string &text):
  text_(text) {
}

VisualText::~VisualText() {
}

const string &
VisualText::getText() const {
  return text_;
}

void
VisualText::setText(const string &text) {
  text_ = text;
}
