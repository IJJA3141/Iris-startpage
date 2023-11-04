#include "left.hpp"

/*
Glib::getenv("HOME") + ".config/Up/test.jpg"
*/

Up::Left::Left() : img_(nullptr), label_(nullptr) {
  this->set_name("left");

  return;
}

Up::Left::~Left() {
  if (this->img_)
    this->img_->unparent();

  if (this->label_)
    this->label_->unparent();
}

void Up::Left::set_childs(Gtk::Image &_img, Gtk::Label &_label) {
  this->img_ = &_img;
  this->label_ = &_label;

  this->img_->set_parent(*this);
  this->label_->set_parent(*this);
}

Gtk::SizeRequestMode Up::Left::get_request_mode_vfunc() const {
  return Gtk::SizeRequestMode::HEIGHT_FOR_WIDTH;
}

void Up::Left::measure_vfunc(Gtk::Orientation orientation, int for_size,
                             int &minimum, int &natural, int &minimum_baseline,
                             int &natural_baseline) const {
  minimum_baseline = -1;
  natural_baseline = -1;

  int dummy_minimum_baseline = 0;
  int dummy_natural_baseline = 0;

  if (orientation == Gtk::Orientation::HORIZONTAL) {
    int height_per_child = for_size;

    if (for_size >= 0) {
      int nvis_children = 0;

      if (this->img_ && this->img_->get_visible())
        ++nvis_children;
      if (this->label_ && this->label_->get_visible())
        ++nvis_children;

      if (nvis_children > 0)
        height_per_child = for_size / nvis_children;
    }

    int child_minimum_width[2] = {0, 0};
    int child_natural_width[2] = {0, 0};

    if (this->img_ && this->img_->get_visible())
      this->img_->measure(orientation, height_per_child, child_minimum_width[0],
                          child_natural_width[0], dummy_minimum_baseline,
                          dummy_natural_baseline);

    if (this->label_ && this->label_->get_visible())
      this->label_->measure(orientation, height_per_child,
                            child_minimum_width[1], child_natural_width[1],
                            dummy_minimum_baseline, dummy_natural_baseline);

    // Request a width equal to the width of the widest visible child.
    minimum = std::max(child_minimum_width[0], child_minimum_width[1]);
    natural = std::max(child_natural_width[0], child_natural_width[1]);
  } else // Gtk::Orientation::VERTICAL
  {
    int child_minimum_height[2] = {0, 0};
    int child_natural_height[2] = {0, 0};
    int nvis_children = 0;

    if (this->img_ && this->img_->get_visible()) {
      ++nvis_children;
      this->img_->measure(orientation, for_size, child_minimum_height[0],
                          child_natural_height[0], dummy_minimum_baseline,
                          dummy_natural_baseline);
    }

    if (this->label_ && this->label_->get_visible()) {
      ++nvis_children;
      this->label_->measure(orientation, for_size, child_minimum_height[1],
                            child_natural_height[1], dummy_minimum_baseline,
                            dummy_natural_baseline);
    }

    // The allocated height will be divided equally among the visible children.
    // Request a height equal to the number of visible children times the height
    // of the highest child.
    minimum = nvis_children *
              std::max(child_minimum_height[0], child_minimum_height[1]);
    natural = nvis_children *
              std::max(child_natural_height[0], child_natural_height[1]);
  }
}

void Up::Left::size_allocate_vfunc(int width, int height, int baseline) {
  // Do something with the space that we have actually been given:
  //(We will not be given heights or widths less than we have requested, though
  // we might get more.)

  // Get number of visible children.
  const bool visible_one = this->img_ && this->img_->get_visible();
  const bool visible_two = this->label_ && this->label_->get_visible();
  int nvis_children = 0;
  if (visible_one)
    ++nvis_children;
  if (visible_two)
    ++nvis_children;

  if (nvis_children <= 0) {
    // No visible child.
    return;
  }

  // Assign space to the children:
  Gtk::Allocation child_allocation_one;
  Gtk::Allocation child_allocation_two;

  // Place the first child at the top-left:
  child_allocation_one.set_x(0);
  child_allocation_one.set_y(0);

  // Make it take up the full width available:
  child_allocation_one.set_width(width);

  if (visible_one) {
    // Divide the height equally among the visible children.
    child_allocation_one.set_height(height / nvis_children);
    this->img_->size_allocate(child_allocation_one, baseline);
  } else
    child_allocation_one.set_height(0);

  // Place the second child below the first child:
  child_allocation_two.set_x(0);
  child_allocation_two.set_y(child_allocation_one.get_height());

  // Make it take up the full width available:
  child_allocation_two.set_width(width);

  // Make it take up the remaining height:
  child_allocation_two.set_height(height - child_allocation_one.get_height());

  if (visible_two) {
    this->label_->size_allocate(child_allocation_two, baseline);
  }
}
