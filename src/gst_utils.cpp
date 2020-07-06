#include "gscam/gst_utils.h"

namespace gscam {

  gboolean print_field (GQuark field, const GValue * value, gpointer pfx)
  {
    gchar *str = gst_value_serialize (value);

    g_print ("%s  %15s: %s\n", (gchar *) pfx, g_quark_to_string (field), str);
    g_free (str);
    return TRUE;
  }

  void print_caps (const GstCaps * caps, const gchar * pfx)
  {
    guint i;

    g_return_if_fail (caps != NULL);

    if (gst_caps_is_any (caps)) {
      g_print ("%sANY\n", pfx);
      return;
    }
    if (gst_caps_is_empty (caps)) {
      g_print ("%sEMPTY\n", pfx);
      return;
    }

    for (i = 0; i < gst_caps_get_size (caps); i++) {
      GstStructure *structure = gst_caps_get_structure (caps, i);

      g_print ("%s%s\n", pfx, gst_structure_get_name (structure));
      gst_structure_foreach (structure, print_field, (gpointer) pfx);
    }
  }

  void print_pad_capabilities(GstElement* element, gchar* pad_name)
  {
    GstPad *pad = NULL;
    GstCaps *caps = NULL;

    /* Retrieve pad */
    pad = gst_element_get_static_pad (element, pad_name);
    if (!pad) {
      g_printerr ("Could not retrieve pad '%s'\n", pad_name);
      return;
    }

    /* Retrieve negotiated caps (or acceptable caps if negotiation is not finished yet) */
    caps = gst_pad_get_current_caps (pad);
    if (!caps)
      caps = gst_pad_query_caps (pad, NULL);

    /* Print and free */
    g_print ("Caps for the %s pad:\n", pad_name);
    print_caps (caps, "      ");
    g_print ("\n");
    gst_caps_unref (caps);
    gst_object_unref (pad);
  }

  void print_pads(GstElement* element, bool src_pads)
  {
    GstIterator* it;
    if (src_pads)
      it = gst_element_iterate_src_pads(element);
    else
      it = gst_element_iterate_sink_pads(element);
    GValue elem = G_VALUE_INIT;
    while( gst_iterator_next( it, &elem ) == GST_ITERATOR_OK )
    {
      print_pad_capabilities( element, gst_element_get_name( g_value_get_object( &elem )));
    }
  }

}
