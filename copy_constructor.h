Vector& Vector::operator=(const Vector& a) // copy assignment
{
  double∗ p = new double[a.sz];
  for (int i=0; i!=a.sz; ++i)
    p[i] = a.elem[i];
  delete[] elem; // delete old elements
  elem = p;
  sz = a.sz;
  return ∗this;
}

