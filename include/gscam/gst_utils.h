#ifndef __GSCAM_GST_UTILS_H
#define __GSCAM_GST_UTILS_H

#include <gst/gst.h>

namespace gscam {

gboolean print_field (GQuark field, const GValue * value, gpointer pfx);
void print_caps (const GstCaps * caps, const gchar * pfx);
void print_pad_capabilities(GstElement* element, gchar* pad_name);
void print_pads(GstElement* element, bool src_pads);

}

#endif // ifndef __GSCAM_GST_UTILS_H
