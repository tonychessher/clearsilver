
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "cgi/cgi.h"
#include "cgi/cgiwrap.h"
#include "util/neo_err.h"

int main (int argc, char **argv, char **envp)
{
  NEOERR *err;
  CGI *cgi;
  char *cs_file;
  char hdf_file[_POSIX_PATH_MAX];
  char *p;
  int x;

  cgi_debug_init (argc,argv);
  cgiwrap_init_std (argc, argv, envp);

  err = cgi_init(&cgi, NULL);
  if (err != STATUS_OK)
  {
    cgi_neo_error(cgi, err);
    nerr_log_error(err);
    return -1;
  }

  cs_file = hdf_get_value (cgi->hdf, "CGI.PathTranslated", NULL);
  if (cs_file == NULL)
  {
    cgi_error (cgi, "No PATH_TRANSLATED var");
    return -1;
  }
  p = strrchr (cs_file, '/');
  if (p)
  {
    *p = '\0';
    err = hdf_set_value (cgi->hdf, "hdf.loadpaths.0", cs_file);
    *p = '/';
    if (err)
    {
      cgi_neo_error(cgi, err);
      nerr_log_error(err);
      return -1;
    }
  }
  snprintf (hdf_file, sizeof(hdf_file), "%s.hdf", cs_file);
  err = hdf_read_file (cgi->hdf, hdf_file);
  if (err && !nerr_handle(&err, NERR_NOT_FOUND))
  {
    cgi_neo_error(cgi, err);
    nerr_log_error(err);
    return -1;
  }
  p = strrchr (cs_file, '.');
  if (p)
  {
    *p = '\0';
    snprintf (hdf_file, sizeof(hdf_file), "%s.hdf", cs_file);
    *p = '.';
    err = hdf_read_file (cgi->hdf, hdf_file);
    if (err && !nerr_handle(&err, NERR_NOT_FOUND))
    {
      cgi_neo_error(cgi, err);
      nerr_log_error(err);
      return -1;
    }
  }
  err = cgi_display (cgi, cs_file);
  if (err != STATUS_OK)
  {
    cgi_neo_error(cgi, err);
    nerr_log_error(err);
    return -1;
  }
  if (hdf_get_int_value (cgi->hdf, "Query.debug", 0))
  {
    cgiwrap_writef("<hr>");
    x = 0;
    while (1)
    {
      char *k, *v;
      err = cgiwrap_iterenv (x, &k, &v);
      if (err != STATUS_OK)
      {
	nerr_log_error(err);
	break;
      }
      if (k == NULL) break;
      cgiwrap_writef("%s = %s<br>", k, v);
      free(k);  
      free(v);
      x++;
    }
    cgiwrap_writef("<pre>");
    hdf_dump(cgi->hdf, NULL);
  }
  return 0;
}
