#!/neo/opt/bin/python
#
# Copyright (C) 2001 by Neotonic Software Corporation
# All Rights Reserved.
#
# hdfhelp.py
#
# This code makes using odb with Clearsilver as "easy as stealing candy
# from a baby". - jeske
#
# How to use:
#
#  rows = tbl.fetchAllRows()
#  rows.hdfExport("CGI.rows", hdf_dataset)
#
#  row  = tbl.fetchRow( ('primary_key', value) )
#  row.hdfExport("CGI.row", hdf_dataset)
#
# How to setup:
#   
#  # define table
#  class AgentsTable(odb.Table):
#    def _defineRows(self):
#      self.d_addColumn("agent_id",kInteger,None,primarykey = 1,autoincrement = 1)
#      self.d_addColumn("login",kVarString,200,notnull=1)
#      self.d_addColumn("ticket_count",kIncInteger,None)
#
#    # make sure you return a subclass of hdfhelp.HdfRow
#
#    def defaultRowClass(self):
#      return hdfhelp.HdfRow
#    def defaultRowListClass(self):
#      return hdfhelp.HdfItemList
#

import string
import neo_cgi
import neo_cs
import neo_util
import odb
import time

import UserList

SECS_IN_MIN = 60
SECS_IN_HOUR = (SECS_IN_MIN * 60)
SECS_IN_DAY = (SECS_IN_HOUR * 24)
SECS_IN_WEEK = (SECS_IN_DAY * 7)
SECS_IN_MONTH = (SECS_IN_DAY * 30)

kYearPos = 0
kMonthPos = 1
kDayPos = 2
kHourPos = 3
kMinutePos = 4
kSecondPos = 5
kWeekdayPos = 6
kJulianDayPos = 7
kDSTPos = 8


def renderDate(then_time,day=0):
    if then_time is None:
        then_time = 0
    then_time = int(then_time)
    if then_time == 0 or then_time == -1:
        return ""
    
    then_tuple = time.localtime(then_time)

    now_tuple = time.localtime(time.time())
    
    if day or (then_tuple[kHourPos]==0 and then_tuple[kMinutePos]==0 and then_tuple[kSecondPos]==0):
        # it's just a date
        if then_tuple[kYearPos] == now_tuple[kYearPos]:
            # no year
            return time.strftime("%m/%d",then_tuple)
        else:
            # add year
            return time.strftime("%m/%d/%Y",then_tuple)

    else:
        # it's a full time/date

        return time.strftime("%m/%d/%Y %H:%M%p",then_tuple)

class HdfRow(odb.Row):
    def hdfExport(self,prefix,hdf_dataset,skip_fields = None, translate_dict = None):

        for col_name,value in self.items():
            if skip_fields and (col_name in skip_fields):
                continue
            try:
                name,col_type,col_options = self._table.getColumnDef(col_name)
            except:
                col_type = odb.kVarString
                col_options = {}
            
	    if (col_name != "value") and (value is not None):
		if type(value) in [ type(0), type(0L) ]:
		    hdf_dataset.setValue(prefix + "." + col_name,"%d" % value)
		else:
                    if translate_dict:
                        for k,v in translate_dict.items():
                            value = string.replace(value,k,v)
		    hdf_dataset.setValue(prefix + "." + col_name,neo_cgi.htmlEscape(value))
                if col_options.get("int_date",0):
                    hdf_dataset.setValue(prefix + "." + col_name + ".string",renderDate(value))
                    hdf_dataset.setValue(prefix + "." + col_name + ".day_string",renderDate(value,day=1))



class HdfItemList(UserList.UserList):
    def hdfExport(self,prefix,hdf_dataset,*extra,**extranamed):
	n = 0
	for row in self:
	    row.hdfExport("%s.%d" % (prefix,n),hdf_dataset,*extra,**extranamed)
	    n = n + 1


def eval_cs(hdf,a_cs_string):
    cs = neo_cs.CS(hdf)
    try:
      cs.parseStr(a_cs_string)
      return cs.render()
    except:
      return "Error in CS tags: %s" % neo_cgi.htmlEscape(repr(a_cs_string))

# ----------------------------

def test():
    import neo_util
    hdf = neo_util.HDF()
    hdf.setValue("foo","1")
    print eval_cs(hdf,"this should say 1  ===> <?cs var:foo ?>")
    

if __name__ == "__main__":
    test()





