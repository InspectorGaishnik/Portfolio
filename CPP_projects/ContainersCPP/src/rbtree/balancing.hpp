#ifndef BALANCING_HPP
#define BALANCING_HPP

#include "rbtree.h"

template <typename T, typename Compare>
void RBTree<T, Compare>::left_rotate(Node<T>* up_to_leftdown) {
  Node<T>* downright_to_up = up_to_leftdown->right_;
  up_to_leftdown->right_ = downright_to_up->left_;
  if (nullptr != downright_to_up->left_) {
    downright_to_up->left_->parent_ = up_to_leftdown;
  }
  downright_to_up->parent_ = up_to_leftdown->parent_;
  if (nullptr == up_to_leftdown->parent_) {
    root_ = downright_to_up;
  } else if (up_to_leftdown == up_to_leftdown->parent_->left_) {
    up_to_leftdown->parent_->left_ = downright_to_up;
  } else {
    up_to_leftdown->parent_->right_ = downright_to_up;
  }
  downright_to_up->left_ = up_to_leftdown;
  up_to_leftdown->parent_ = downright_to_up;
}

template <typename T, typename Compare>
void RBTree<T, Compare>::right_rotate(Node<T>* up_to_rightdown) {
  Node<T>* downleft_to_up = up_to_rightdown->left_;
  up_to_rightdown->left_ = downleft_to_up->right_;
  if (nullptr != downleft_to_up->right_) {
    downleft_to_up->right_->parent_ = up_to_rightdown;
  }
  downleft_to_up->parent_ = up_to_rightdown->parent_;
  if (nullptr == up_to_rightdown->parent_) {
    root_ = downleft_to_up;
  } else if (up_to_rightdown == up_to_rightdown->parent_->right_) {
    up_to_rightdown->parent_->right_ = downleft_to_up;
  } else {
    up_to_rightdown->parent_->left_ = downleft_to_up;
  }
  downleft_to_up->right_ = up_to_rightdown;
  up_to_rightdown->parent_ = downleft_to_up;
}

template <typename T, typename Compare>
void RBTree<T, Compare>::handle_red_uncle_case(Node<T>*& k, Node<T>* uncle) {
  k->parent_->color_ = Color::Black;
  uncle->color_ = Color::Black;
  k->parent_->parent_->color_ = Color::Red;
  k = k->parent_->parent_;
}

template <typename T, typename Compare>
void RBTree<T, Compare>::handle_black_uncle_case(Node<T>*& k) {
  if (k == k->parent_->right_) {
    k = k->parent_;
    left_rotate(k);
  }
  k->parent_->color_ = Color::Black;
  k->parent_->parent_->color_ = Color::Red;
  right_rotate(k->parent_->parent_);
}

template <typename T, typename Compare>
void RBTree<T, Compare>::handle_left_parent_case(Node<T>*& k) {
  Node<T>* uncle = k->parent_->parent_->right_;

  if (uncle && uncle->color_ == Color::Red) {
    handle_red_uncle_case(k, uncle);
  } else {
    handle_black_uncle_case(k);
  }
}

template <typename T, typename Compare>
void RBTree<T, Compare>::handle_right_parent_case(Node<T>*& k) {
  Node<T>* uncle = k->parent_->parent_->left_;

  if (uncle && uncle->color_ == Color::Red) {
    handle_red_uncle_case(k, uncle);
  } else {
    if (k == k->parent_->left_) {
      k = k->parent_;
      right_rotate(k);
    }
    k->parent_->color_ = Color::Black;
    k->parent_->parent_->color_ = Color::Red;
    left_rotate(k->parent_->parent_);
  }
}

template <typename T, typename Compare>
void RBTree<T, Compare>::handle_red_sibling_case(Node<T>*& x, Node<T>* w,
                                                 Node<T>* x_parent) {
  w->color_ = Color::Black;
  x->parent_->color_ = Color::Red;
  left_rotate(x->parent_);
  w = x_parent->right_;
}

template <typename T, typename Compare>
void RBTree<T, Compare>::handle_black_sibling_case(Node<T>*& x, Node<T>* w,
                                                   Node<T>* x_parent) {
  if (w && (!w->right_ || w->right_->color_ == Color::Black)) {
    if (w->left_) w->left_->color_ = Color::Black;
    w->color_ = Color::Red;
    right_rotate(w);
    w = x_parent->right_;
  }

  if (w) {
    w->color_ = x_parent->color_;
    x_parent->color_ = Color::Black;
    if (w->right_) w->right_->color_ = Color::Black;
    left_rotate(x_parent);
  }
  x = root_;
}

template <typename T, typename Compare>
void RBTree<T, Compare>::handle_double_black_case(Node<T>*& x, Node<T>* w,
                                                  Node<T>* x_parent) {
  if (w && (!w->left_ || w->left_->color_ == Color::Black) &&
      (!w->right_ || w->right_->color_ == Color::Black)) {
    w->color_ = Color::Red;
    x = x_parent;
  } else {
    handle_black_sibling_case(x, w, x_parent);
  }
}
template <typename T, typename Compare>
void RBTree<T, Compare>::fix_insert(Node<T>* k) {
  bool should_continue = true;

  while (should_continue) {
    if (k != root_ && k->parent_->color_ == Color::Red) {
      if (k->parent_ == k->parent_->parent_->left_) {
        handle_left_parent_case(k);
      } else {
        handle_right_parent_case(k);
      }
    } else {
      should_continue = false;
    }
  }

  root_->color_ = Color::Black;
}

template <typename T, typename Compare>
bool RBTree<T, Compare>::should_continue_fix_delete(Node<T>* x) {
  return x != root_ && (!x || x->color_ == Color::Black);
}

template <typename T, typename Compare>
void RBTree<T, Compare>::handle_null_x_case(Node<T>*& x, Node<T>*& x_parent,
                                            bool& should_continue) {
  if (!x) {
    if (x_parent == root_) {
      should_continue = false;
    } else {
      x = x_parent;
    }
  }
}

template <typename T, typename Compare>
void RBTree<T, Compare>::process_left_child_case(Node<T>*& x,
                                                 Node<T>*& x_parent) {
  x_parent = x->parent_;
  Node<T>* w = x->parent_->right_;

  if (w && w->color_ == Color::Red) {
    handle_red_sibling_case(x, w, x_parent);
    w = x_parent->right_;
  }

  handle_double_black_case(x, w, x_parent);
}

template <typename T, typename Compare>
void RBTree<T, Compare>::process_right_child_case(Node<T>*& x,
                                                  Node<T>*& x_parent) {
  x_parent = x->parent_;
  Node<T>* w = x->parent_->left_;

  if (w && w->color_ == Color::Red) {
    w->color_ = Color::Black;
    x->parent_->color_ = Color::Red;
    right_rotate(x->parent_);
    w = x_parent->left_;
  }

  if (w && (!w->right_ || w->right_->color_ == Color::Black) &&
      (!w->left_ || w->left_->color_ == Color::Black)) {
    w->color_ = Color::Red;
    x = x_parent;
  } else {
    if (w && (!w->left_ || w->left_->color_ == Color::Black)) {
      if (w->right_) w->right_->color_ = Color::Black;
      w->color_ = Color::Red;
      left_rotate(w);
      w = x_parent->left_;
    }

    if (w) {
      w->color_ = x_parent->color_;
      x_parent->color_ = Color::Black;
      if (w->left_) w->left_->color_ = Color::Black;
      right_rotate(x_parent);
    }
    x = root_;
  }
}

template <typename T, typename Compare>
void RBTree<T, Compare>::fix_delete(Node<T>* x) {
  Node<T>* x_parent = nullptr;
  bool should_continue = true;

  while (should_continue) {
    if (should_continue_fix_delete(x)) {
      handle_null_x_case(x, x_parent, should_continue);

      if (should_continue) {
        if (x == x->parent_->left_) {
          process_left_child_case(x, x_parent);
        } else {
          process_right_child_case(x, x_parent);
        }
      }
    } else {
      should_continue = false;
    }
  }

  if (x) x->color_ = Color::Black;
}

template <typename T, typename Compare>
void RBTree<T, Compare>::transplant(Node<T>* u, Node<T>* v) {
  if (u->parent_ == nullptr) {
    root_ = v;
  } else if (u == u->parent_->left_) {
    u->parent_->left_ = v;
  } else {
    u->parent_->right_ = v;
  }

  if (v != nullptr) {
    v->parent_ = u->parent_;
  }
}

#endif