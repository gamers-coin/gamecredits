include $(top_srcdir)/src/Makefile.include

AM_CPPFLAGS += -I$(top_srcdir)/src \
  -I$(top_builddir)/src/qt \
  -I$(top_builddir)/src/qt/forms \
  $(PROTOBUF_CFLAGS) \
  $(QR_CFLAGS)
bin_PROGRAMS = gamecredits-qt
noinst_LIBRARIES = libgamecreditsqt.a
SUBDIRS = . $(BUILD_TEST_QT)
DIST_SUBDIRS = . test

# gamecredits qt core #
QT_TS = \
  locale/gamecredits_ach.ts \
  locale/gamecredits_af_ZA.ts \
  locale/gamecredits_ar.ts \
  locale/gamecredits_be_BY.ts \
  locale/gamecredits_bg.ts \
  locale/gamecredits_bs.ts \
  locale/gamecredits_ca_ES.ts \
  locale/gamecredits_ca.ts \
  locale/gamecredits_ca@valencia.ts \
  locale/gamecredits_cmn.ts \
  locale/gamecredits_cs.ts \
  locale/gamecredits_cy.ts \
  locale/gamecredits_da.ts \
  locale/gamecredits_de.ts \
  locale/gamecredits_el_GR.ts \
  locale/gamecredits_en.ts \
  locale/gamecredits_eo.ts \
  locale/gamecredits_es_CL.ts \
  locale/gamecredits_es_DO.ts \
  locale/gamecredits_es_MX.ts \
  locale/gamecredits_es.ts \
  locale/gamecredits_es_UY.ts \
  locale/gamecredits_et.ts \
  locale/gamecredits_eu_ES.ts \
  locale/gamecredits_fa_IR.ts \
  locale/gamecredits_fa.ts \
  locale/gamecredits_fi.ts \
  locale/gamecredits_fr_CA.ts \
  locale/gamecredits_fr.ts \
  locale/gamecredits_gl.ts \
  locale/gamecredits_gu_IN.ts \
  locale/gamecredits_he.ts \
  locale/gamecredits_hi_IN.ts \
  locale/gamecredits_hr.ts \
  locale/gamecredits_hu.ts \
  locale/gamecredits_id_ID.ts \
  locale/gamecredits_it.ts \
  locale/gamecredits_ja.ts \
  locale/gamecredits_ka.ts \
  locale/gamecredits_kk_KZ.ts \
  locale/gamecredits_ko_KR.ts \
  locale/gamecredits_ky.ts \
  locale/gamecredits_la.ts \
  locale/gamecredits_lt.ts \
  locale/gamecredits_lv_LV.ts \
  locale/gamecredits_mn.ts \
  locale/gamecredits_ms_MY.ts \
  locale/gamecredits_nb.ts \
  locale/gamecredits_nl.ts \
  locale/gamecredits_pam.ts \
  locale/gamecredits_pl.ts \
  locale/gamecredits_pt_BR.ts \
  locale/gamecredits_pt_PT.ts \
  locale/gamecredits_ro_RO.ts \
  locale/gamecredits_ru.ts \
  locale/gamecredits_sah.ts \
  locale/gamecredits_sk.ts \
  locale/gamecredits_sl_SI.ts \
  locale/gamecredits_sq.ts \
  locale/gamecredits_sr.ts \
  locale/gamecredits_sv.ts \
  locale/gamecredits_th_TH.ts \
  locale/gamecredits_tr.ts \
  locale/gamecredits_uk.ts \
  locale/gamecredits_ur_PK.ts \
  locale/gamecredits_uz@Cyrl.ts \
  locale/gamecredits_vi.ts \
  locale/gamecredits_vi_VN.ts \
  locale/gamecredits_zh_CN.ts \
  locale/gamecredits_zh_HK.ts \
  locale/gamecredits_zh_TW.ts

QT_FORMS_UI = \
  forms/aboutdialog.ui \
  forms/addressbookpage.ui \
  forms/askpassphrasedialog.ui \
  forms/coincontroldialog.ui \
  forms/editaddressdialog.ui \
  forms/helpmessagedialog.ui \
  forms/intro.ui \
  forms/openuridialog.ui \
  forms/optionsdialog.ui \
  forms/overviewpage.ui \
  forms/receivecoinsdialog.ui \
  forms/receiverequestdialog.ui \
  forms/rpcconsole.ui \
  forms/sendcoinsdialog.ui \
  forms/sendcoinsentry.ui \
  forms/signverifymessagedialog.ui \
  forms/transactiondescdialog.ui

QT_MOC_CPP = \
  moc_addressbookpage.cpp \
  moc_addresstablemodel.cpp \
  moc_askpassphrasedialog.cpp \
  moc_gamecreditsaddressvalidator.cpp \
  moc_gamecreditsamountfield.cpp \
  moc_gamecreditsgui.cpp \
  moc_gamecreditsunits.cpp \
  moc_clientmodel.cpp \
  moc_coincontroldialog.cpp \
  moc_coincontroltreewidget.cpp \
  moc_csvmodelwriter.cpp \
  moc_editaddressdialog.cpp \
  moc_guiutil.cpp \
  moc_intro.cpp \
  moc_macdockiconhandler.cpp \
  moc_macnotificationhandler.cpp \
  moc_monitoreddatamapper.cpp \
  moc_notificator.cpp \
  moc_openuridialog.cpp \
  moc_optionsdialog.cpp \
  moc_optionsmodel.cpp \
  moc_overviewpage.cpp \
  moc_paymentserver.cpp \
  moc_qvalidatedlineedit.cpp \
  moc_qvaluecombobox.cpp \
  moc_receivecoinsdialog.cpp \
  moc_receiverequestdialog.cpp \
  moc_recentrequeststablemodel.cpp \
  moc_rpcconsole.cpp \
  moc_sendcoinsdialog.cpp \
  moc_sendcoinsentry.cpp \
  moc_signverifymessagedialog.cpp \
  moc_splashscreen.cpp \
  moc_trafficgraphwidget.cpp \
  moc_transactiondesc.cpp \
  moc_transactiondescdialog.cpp \
  moc_transactionfilterproxy.cpp \
  moc_transactiontablemodel.cpp \
  moc_transactionview.cpp \
  moc_utilitydialog.cpp \
  moc_walletframe.cpp \
  moc_walletmodel.cpp \
  moc_walletview.cpp

GAMECREDITS_MM = \
  macdockiconhandler.mm \
  macnotificationhandler.mm

QT_MOC = \
  gamecredits.moc \
  intro.moc \
  overviewpage.moc \
  rpcconsole.moc

QT_QRC_CPP = qrc_gamecredits.cpp
QT_QRC = gamecredits.qrc

PROTOBUF_CC = paymentrequest.pb.cc
PROTOBUF_H = paymentrequest.pb.h
PROTOBUF_PROTO = paymentrequest.proto

GAMECREDITS_QT_H = \
  addressbookpage.h \
  addresstablemodel.h \
  askpassphrasedialog.h \
  gamecreditsaddressvalidator.h \
  gamecreditsamountfield.h \
  gamecreditsgui.h \
  gamecreditsunits.h \
  clientmodel.h \
  coincontroldialog.h \
  coincontroltreewidget.h \
  csvmodelwriter.h \
  editaddressdialog.h \
  guiconstants.h \
  guiutil.h \
  intro.h \
  macdockiconhandler.h \
  macnotificationhandler.h \
  monitoreddatamapper.h \
  notificator.h \
  openuridialog.h \
  optionsdialog.h \
  optionsmodel.h \
  overviewpage.h \
  paymentrequestplus.h \
  paymentserver.h \
  qvalidatedlineedit.h \
  qvaluecombobox.h \
  receivecoinsdialog.h \
  receiverequestdialog.h \
  recentrequeststablemodel.h \
  rpcconsole.h \
  sendcoinsdialog.h \
  sendcoinsentry.h \
  signverifymessagedialog.h \
  splashscreen.h \
  trafficgraphwidget.h \
  transactiondesc.h \
  transactiondescdialog.h \
  transactionfilterproxy.h \
  transactionrecord.h \
  transactiontablemodel.h \
  transactionview.h \
  utilitydialog.h \
  walletframe.h \
  walletmodel.h \
  walletmodeltransaction.h \
  walletview.h \
  winshutdownmonitor.h

RES_ICONS = \
  res/icons/add.png \
  res/icons/address-book.png \
  res/icons/gamecredits.ico \
  res/icons/gamecredits.png \
  res/icons/gamecredits_testnet.ico \
  res/icons/gamecredits_testnet.png \
  res/icons/clock1.png \
  res/icons/clock2.png \
  res/icons/clock3.png \
  res/icons/clock4.png \
  res/icons/clock5.png \
  res/icons/configure.png \
  res/icons/connect0_16.png \
  res/icons/connect1_16.png \
  res/icons/connect2_16.png \
  res/icons/connect3_16.png \
  res/icons/connect4_16.png \
  res/icons/debugwindow.png \
  res/icons/edit.png \
  res/icons/editcopy.png \
  res/icons/editpaste.png \
  res/icons/export.png \
  res/icons/filesave.png \
  res/icons/history.png \
  res/icons/key.png \
  res/icons/lock_closed.png \
  res/icons/lock_open.png \
  res/icons/overview.png \
  res/icons/qrcode.png \
  res/icons/quit.png \
  res/icons/receive.png \
  res/icons/remove.png \
  res/icons/send.png \
  res/icons/synced.png \
  res/icons/toolbar.png \
  res/icons/toolbar_testnet.png \
  res/icons/transaction0.png \
  res/icons/transaction2.png \
  res/icons/transaction_conflicted.png \
  res/icons/tx_inout.png \
  res/icons/tx_input.png \
  res/icons/tx_output.png \
  res/icons/tx_mined.png

GAMECREDITS_QT_CPP = \
  gamecredits.cpp \
  gamecreditsaddressvalidator.cpp \
  gamecreditsamountfield.cpp \
  gamecreditsgui.cpp \
  gamecreditsunits.cpp \
  clientmodel.cpp \
  csvmodelwriter.cpp \
  guiutil.cpp \
  intro.cpp \
  monitoreddatamapper.cpp \
  notificator.cpp \
  optionsdialog.cpp \
  optionsmodel.cpp \
  qvalidatedlineedit.cpp \
  qvaluecombobox.cpp \
  rpcconsole.cpp \
  splashscreen.cpp \
  trafficgraphwidget.cpp \
  utilitydialog.cpp \
  winshutdownmonitor.cpp

if ENABLE_WALLET
GAMECREDITS_QT_CPP += \
  addressbookpage.cpp \
  addresstablemodel.cpp \
  askpassphrasedialog.cpp \
  coincontroldialog.cpp \
  coincontroltreewidget.cpp \
  editaddressdialog.cpp \
  openuridialog.cpp \
  overviewpage.cpp \
  paymentrequestplus.cpp \
  paymentserver.cpp \
  receivecoinsdialog.cpp \
  receiverequestdialog.cpp \
  recentrequeststablemodel.cpp \
  sendcoinsdialog.cpp \
  sendcoinsentry.cpp \
  signverifymessagedialog.cpp \
  transactiondesc.cpp \
  transactiondescdialog.cpp \
  transactionfilterproxy.cpp \
  transactionrecord.cpp \
  transactiontablemodel.cpp \
  transactionview.cpp \
  walletframe.cpp \
  walletmodel.cpp \
  walletmodeltransaction.cpp \
  walletview.cpp
endif

RES_IMAGES = \
  res/images/about.png \
  res/images/splash.png \
  res/images/splash_testnet.png

RES_MOVIES = $(wildcard res/movies/spinner-*.png)

GAMECREDITS_RC = res/gamecredits-qt-res.rc

libgamecreditsqt_a_CPPFLAGS = $(AM_CPPFLAGS) $(QT_INCLUDES) \
  -I$(top_srcdir)/src/qt/forms $(QT_DBUS_INCLUDES)
libgamecreditsqt_a_SOURCES = $(GAMECREDITS_QT_CPP) $(GAMECREDITS_QT_H) $(QT_FORMS_UI) \
  $(QT_QRC) $(QT_TS) $(PROTOBUF_PROTO) $(RES_ICONS) $(RES_IMAGES) $(RES_MOVIES)

nodist_libgamecreditsqt_a_SOURCES = $(QT_MOC_CPP) $(QT_MOC) $(PROTOBUF_CC) \
  $(PROTOBUF_H) $(QT_QRC_CPP)

BUILT_SOURCES = $(nodist_libgamecreditsqt_a_SOURCES)

#Generating these with a half-written protobuf header leads to wacky results.
#This makes sure it's done.
$(QT_MOC): $(PROTOBUF_H)
$(QT_MOC_CPP): $(PROTOBUF_H)

# gamecredits-qt binary #
gamecredits_qt_CPPFLAGS = $(AM_CPPFLAGS) $(QT_INCLUDES) \
  -I$(top_srcdir)/src/qt/forms
gamecredits_qt_SOURCES = gamecredits.cpp
if TARGET_DARWIN
  gamecredits_qt_SOURCES += $(GAMECREDITS_MM)
endif
if TARGET_WINDOWS
  gamecredits_qt_SOURCES += $(GAMECREDITS_RC)
endif
gamecredits_qt_LDADD = libgamecreditsqt.a $(LIBGAMECREDITS_SERVER)
if ENABLE_WALLET
gamecredits_qt_LDADD += $(LIBGAMECREDITS_WALLET)
endif
gamecredits_qt_LDADD += $(LIBGAMECREDITS_CLI) $(LIBGAMECREDITS_COMMON) $(LIBLEVELDB) $(LIBMEMENV) \
  $(BOOST_LIBS) $(QT_LIBS) $(QT_DBUS_LIBS) $(QR_LIBS) $(PROTOBUF_LIBS) $(BDB_LIBS)
gamecredits_qt_LDFLAGS = $(QT_LDFLAGS)

# forms/foo.h -> forms/ui_foo.h
QT_FORMS_H=$(join $(dir $(QT_FORMS_UI)),$(addprefix ui_, $(notdir $(QT_FORMS_UI:.ui=.h))))

#locale/foo.ts -> locale/foo.qm
QT_QM=$(QT_TS:.ts=.qm)

.PHONY: FORCE
.SECONDARY: $(QT_QM)

gamecreditstrings.cpp: FORCE
	$(MAKE) -C $(top_srcdir)/src qt/gamecreditstrings.cpp

translate: gamecreditstrings.cpp $(QT_FORMS_UI) $(QT_FORMS_UI) $(GAMECREDITS_QT_CPP) $(GAMECREDITS_QT_H) $(GAMECREDITS_MM)
	@test -n $(LUPDATE) || echo "lupdate is required for updating translations"
	@QT_SELECT=$(QT_SELECT) $(LUPDATE) $^ -locations relative -no-obsolete -ts locale/gamecredits_en.ts

$(QT_QRC_CPP): $(QT_QRC) $(QT_QM) $(QT_FORMS_H) $(RES_ICONS) $(RES_IMAGES) $(RES_MOVIES) $(PROTOBUF_H)
	@cd $(abs_srcdir); test -f $(RCC) && QT_SELECT=$(QT_SELECT) $(RCC) -name gamecredits -o $(abs_builddir)/$@ $< || \
	  echo error: could not build $@
	$(SED) -e '/^\*\*.*Created:/d' $@ > $@.n && mv $@{.n,}
	$(SED) -e '/^\*\*.*by:/d' $@  > $@.n && mv $@{.n,}

CLEANFILES = $(BUILT_SOURCES) $(QT_QM) $(QT_FORMS_H) *.gcda *.gcno
