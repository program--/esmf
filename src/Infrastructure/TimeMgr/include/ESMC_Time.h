// $Id: ESMC_Time.h,v 1.21 2003/05/02 01:01:07 eschwab Exp $
//
// Earth System Modeling Framework
// Copyright 2002-2003, University Corporation for Atmospheric Research,
// Massachusetts Institute of Technology, Geophysical Fluid Dynamics
// Laboratory, University of Michigan, National Centers for Environmental
// Prediction, Los Alamos National Laboratory, Argonne National Laboratory,
// NASA Goddard Space Flight Center.
// Licensed under the GPL.
//
// ESMF Time C++ definition include file
//
// (all lines below between the !BOP and !EOP markers will be included in
//  the automated document processing.)
//-------------------------------------------------------------------------
//
 // these lines prevent this file from being read more than once if it
 // ends up being included multiple times

 #ifndef ESMC_TIME_H
 #define ESMC_TIME_H

//-------------------------------------------------------------------------

 // put any constants or macros which apply to the whole component in this file.
 // anything public or esmf-wide should be up higher at the top level
 // include files.
 #include <ESMF_TimeMgr.inc>

//-------------------------------------------------------------------------
//BOP
// !CLASS: ESMC_Time - represents a specific point in time
//
// !DESCRIPTION:
//
// The code in this file defines the C++ {\tt Time} members and method
// signatures (prototypes).  The companion file {\tt ESMC\_Time.C} contains
// the full code (bodies) for the {\tt Time] methods.
//
// A {\tt Time} inherits from the {\tt BaseTime} base class and is designed
// to represent a specific point in time which is dependent upon a calendar
// type.
//
// {\tt Time} inherits from the base class {\tt BaseTime}.  As such, it gains
// the core representation of time as well as its associated methods.
// {\tt Time} further specializes {\tt BaseTime} by adding shortcut methods
// to set and get a {\tt Time} in a natural way with appropriate unit
// combinations, as per the requirements.  A {\tt Time} is calendar-dependent,
// since its largest units of time are months and years.  {\tt Time} also
// defines special methods for getting the day of the year, day of the week,
// middle of the month, and synchronizing with a real-time clock.  {\tt Time}
// adds its associated {\tt Calendar} and local Timezone attributes to
// {\tt BaseTime}.
//
// A time value of zero (both whole and numerator) will correspond
// to the Julian date of zero UTC.  This will ease conversions 
// between Julian and Gregorian calendars.
//
//-------------------------------------------------------------------------
//
// !USES:
 #include <ESMC_Base.h>           // inherited Base class
 #include <ESMC_BaseTime.h>       // inherited Time class
 #include <ESMC_Calendar.h>       // associated Calendar class
 #include <ESMC_TimeInterval.h> 

// !PUBLIC TYPES:
 class ESMC_Time;

// !PRIVATE TYPES:
 // class configuration type:  not needed for Time

 // class definition type
 class ESMC_Time : public ESMC_BaseTime { // inherits ESMC_BaseTime 
                                          // TODO: (& ESMC_Base class when
                                          // fully aligned with F90 equiv)
  private:   // corresponds to F90 module 'type ESMF_Time' members 
    class ESMC_Calendar *Calendar;    // associated calendar
    int Timezone;                     // Offset from GMT

// !PUBLIC MEMBER FUNCTIONS:

  public:
    // Init method for native C++ use
    int ESMC_TimeInit(ESMC_Calendar *cal, int tz, const char *timeList, ...);

    // Init method to support the F90 optional arguments interface
    int ESMC_TimeInit(ESMF_IKIND_I8 *YR=0, int *MM=0, int *DD=0,
                      ESMF_IKIND_I8 *D=0,
                      int *H=0, int *M=0, ESMF_IKIND_I8 *S=0,
                      int *MS=0, int *US=0, int *NS=0,
                      double *d_=0, double *h_=0, double *m_=0, double *s_=0,
                      double *ms_=0, double *us_=0, double *ns_=0,
                      int *Sn=0, int *Sd=0, ESMC_Calendar *cal=0, int *tz=0);

    // Time doesn't need configuration, hence GetConfig/SetConfig
    // methods are not required

    // accessor methods
    // all get/set routines perform signed conversions, where applicable

    // generic interface -- via variable argument lists
    //   can map to F90 named-optional-arguments interface
    // (TMG 2.1, 2.5.1, 2.5.6)
    int ESMC_TimeGet(const char *timeList, ...) const;
    // e.g. ESMC_TimeGet("YR:MM:DD", (int *)YR,(int *)MM, (int *)DD);

    int ESMC_TimeSet(const char *timeList, ...);
    // e.g. ESMC_TimeSet("s" , (double) s);

    // Get/Set methods to support the F90 optional arguments interface
    int ESMC_TimeGet(ESMF_IKIND_I8 *YR=0, int *MM=0, int *DD=0,
                     ESMF_IKIND_I8 *D=0,
                     int *H=0, int *M=0, ESMF_IKIND_I8 *S=0,
                     int *MS=0, int *US=0, int *NS=0,
                     double *d_=0, double *h_=0, double *m_=0, double *s_=0,
                     double *ms_=0, double *us_=0, double *ns_=0,
                     int *Sn=0, int *Sd=0) const;

    int ESMC_TimeSet(ESMF_IKIND_I8 *YR=0, int *MM=0, int *DD=0,
                     ESMF_IKIND_I8 *D=0,
                     int *H=0, int *M=0, ESMF_IKIND_I8 *S=0,
                     int *MS=0, int *US=0, int *NS=0,
                     double *d_=0, double *h_=0, double *m_=0, double *s_=0,
                     double *ms_=0, double *us_=0, double *ns_=0,
                     int *Sn=0, int *Sd=0);

    int ESMC_TimeGetCalendar(ESMC_Calendar **calendar) const;  // pointer
    int ESMC_TimeGetCalendar(ESMC_Calendar  *calendar) const;  // copy
    int ESMC_TimeSetCalendar(ESMC_Calendar  *calendar);

    bool ESMC_TimeIsSameCal(ESMC_Time *time, int *rc) const;

    int ESMC_TimeGetTimeZone(int *timezone) const;  // (TMG 2.5.1)
    int ESMC_TimeSetTimeZone(int  timezone);

    // return in string format (TMG 2.4.7)
    int ESMC_TimeGetString(char *timeString) const;

    int ESMC_TimeGetDayOfYear(double *dayOfYear) const; // (TMG 2.5.2)
    int ESMC_TimeGetDayOfYear(int *dayOfYear) const;
    int ESMC_TimeGetDayOfYear(ESMC_TimeInterval *dayOfYear) const;

    int ESMC_TimeGetDayOfWeek(int *dayOfWeek) const;    // (TMG 2.5.3)
    int ESMC_TimeGetDayOfMonth(int *dayOfMonth) const;  // (TMG 2.5.4)
    int ESMC_TimeGetMidMonth(ESMC_Time *midMonth) const;
                                                        // (TMG 2.5.5)
    // to support ESMC_Clock::SyncToWallClock() and TMG 2.5.7
    int ESMC_TimeGetRealTime(void);

    // copy or assign from ESMC_BaseTime expressions
    // TODO:  should be implicit ?
    ESMC_Time& operator=(const ESMC_BaseTime &);  

    // required methods inherited and overridden from the ESMC_Base class

    // for persistence/checkpointing
    int ESMC_TimeRead(ESMF_IKIND_I8 S, int Sn, int Sd,
                      ESMC_Calendar *cal, int timeZone);
    int ESMC_TimeWrite(ESMF_IKIND_I8 *S, int *Sn, int *Sd,
                       ESMC_Calendar *cal, int *timeZone) const;

    // internal validation
    int ESMC_TimeValidate(const char *options=0) const;

    // for testing/debugging
    int ESMC_TimePrint(const char *options=0) const;

    // native C++ constructors/destructors
    ESMC_Time(void);
    ESMC_Time(ESMF_IKIND_I8 S, int Sn, int Sd, ESMC_Calendar *cal,
              int timezone=0);
    ~ESMC_Time(void);

 // < declare the rest of the public interface methods here >

    friend class ESMC_Calendar;

// !PRIVATE MEMBER FUNCTIONS:
//
  private:
//
 // < declare private interface methods here >
//
//EOP
//-------------------------------------------------------------------------

 };   // end class ESMC_Time

 #endif // ESMC_TIME_H
