from ROOT import gROOT, gStyle, gSystem, TLatex, TMarker, TLine
import subprocess

def cmsPrelimHI(canvas, lumi):
    l = TLatex();
    l.SetNDC();
    l.SetTextFont(42);
    l.SetTextAlign(11);

    canvas.cd()
    l.SetTextSize(0.042);
    #l.DrawLatex(0.2, 1. - canvas.GetTopMargin()*2.5, 'Preliminary')
    l.DrawLatex(0.47, 1. - canvas.GetTopMargin()*2.5,
                'CMS PbPb #sqrt{s_{NN}} = 2.76 TeV'
                )
    l.SetTextSize(0.04);
    l.DrawLatex(0.51, 1. - canvas.GetTopMargin()*4.0,
                'Cent. 0-100%, |y| < 2.4'
                )
    l.DrawLatex(0.51, 1. - canvas.GetTopMargin()*5.3,
                'p_{T}^{#mu} > 4 GeV/c'
                )
    l.DrawLatex(0.51, 1. - canvas.GetTopMargin()*6.6,
                'L_{{int}} = {0:0.0f} #mub^{{-1}}'.format(lumi)
                )
    l.DrawLatex(0.7, 1. - canvas.GetTopMargin()*9,
                "data")
    l.DrawLatex(0.7, 1. - canvas.GetTopMargin()*10,
                "total fit")
    l.DrawLatex(0.7, 1. - canvas.GetTopMargin()*11,
                "background")
    M = TMarker(11.35, 425, 20)
    M.SetMarkerSize(1)
    M.DrawMarker(11.35, 425)

    L1 = TLine();
    L1.SetLineWidth(2)
    L1.SetLineColor(4)
    L1.DrawLineNDC(0.62, 1. - canvas.GetTopMargin()*9.75,
                   0.68, 1. - canvas.GetTopMargin()*9.75)

    L2 = TLine();
    L2.SetLineWidth(2)
    L2.SetLineColor(4)
    L2.SetLineStyle(2)
    L2.DrawLineNDC(0.62, 1. - canvas.GetTopMargin()*10.75,
                   0.68, 1. - canvas.GetTopMargin()*10.75)

    canvas.Update()

def cmsPrelimPP(canvas, lumi):
    l = TLatex();
    l.SetNDC();
    l.SetTextFont(42);
    l.SetTextAlign(11);

    canvas.cd()
    l.SetTextSize(0.042);
    #l.DrawLatex(0.2, 1. - canvas.GetTopMargin()*2.5, 'Preliminary')
    l.DrawLatex(0.51, 1. - canvas.GetTopMargin()*2.5,
                'CMS pp #sqrt{s} = 2.76 TeV'
                )   
    l.SetTextSize(0.04);
    l.DrawLatex(0.55, 1. - canvas.GetTopMargin()*4.0,
                '|y| < 2.4'
                )   
    l.DrawLatex(0.55, 1. - canvas.GetTopMargin()*5.3,
                'p_{T}^{#mu} > 4 GeV/c'
                )   
    l.DrawLatex(0.55, 1. - canvas.GetTopMargin()*6.6,
                'L_{{int}} = {0:0.0f} nb^{{-1}}'.format(lumi)
                )   
    l.DrawLatex(0.7, 1. - canvas.GetTopMargin()*9,
               "data")
    l.DrawLatex(0.7, 1. - canvas.GetTopMargin()*10,
               "total fit")
    l.DrawLatex(0.7, 1. - canvas.GetTopMargin()*11,
               "background")

    M = TMarker(11.35, 27.5, 20) 
    M.SetMarkerSize(1)
    M.DrawMarker(11.35, 27.5)

    L1 = TLine();
    L1.SetLineWidth(2)
    L1.SetLineColor(4)
    L1.DrawLineNDC(0.62, 1. - canvas.GetTopMargin()*9.75,
                   0.68, 1. - canvas.GetTopMargin()*9.75)

    L2 = TLine();
    L2.SetLineWidth(2)
    L2.SetLineColor(4)
    L2.SetLineStyle(2)
    L2.DrawLineNDC(0.62, 1. - canvas.GetTopMargin()*10.75,
                   0.68, 1. - canvas.GetTopMargin()*10.75)

    canvas.Update()

gROOT.SetStyle('Plain')
gStyle.SetPadTickX(1)
gStyle.SetPadTickY(1)
gStyle.SetOptStat("iouRMe")
gStyle.SetPalette(1)
gStyle.SetOptFit(1112)
gStyle.SetOptTitle(0)

gStyle.SetCanvasDefH(600) ## Height of canvas
gStyle.SetCanvasDefW(600) ## Width of canvas
gStyle.SetErrorX(0.)

gStyle.SetMarkerStyle(20)

## For the fit/function:
gStyle.SetFuncColor(2)
gStyle.SetFuncStyle(1)
gStyle.SetFuncWidth(1)

##  Margins:
gStyle.SetPadTopMargin(0.05)
gStyle.SetPadBottomMargin(0.13)
gStyle.SetPadLeftMargin(0.16) ## was 0.16
gStyle.SetPadRightMargin(0.05)## was 0.02

gStyle.SetTitleColor(1, "XYZ")
gStyle.SetTitleFont(42, "XYZ")
gStyle.SetTitleSize(0.045, "XYZ")
gStyle.SetTitleXOffset(1.2)
gStyle.SetTitleYOffset(1.4) ## was 1.25

##  For the axis labels:
gStyle.SetLabelColor(1, "XYZ")
gStyle.SetLabelFont(42, "XYZ")
gStyle.SetLabelOffset(0.007, "XYZ")
gStyle.SetLabelSize(0.04, "XYZ")

if (gSystem.DynamicPathName("libFWCoreFWLite.so",True)):
    print "adding RooFit ...",
    scramCmd = ['scram','tool','info','roofitcore']
    grepCmd = ['grep', 'INCLUDE']
    pscram = subprocess.Popen(scramCmd, stdout = subprocess.PIPE)
    pgrep = subprocess.Popen(grepCmd, stdin=pscram.stdout,
                             stdout=subprocess.PIPE)
    pscram.stdout.close()
    output = pgrep.communicate()[0]
    if (pgrep.returncode == 0):
        roofitinc = output.split("=")[1].rstrip()
        ## print roofitinc
        gROOT.GetInterpreter().AddIncludePath(roofitinc)
        roofitinc = '-I"' + roofitinc + '"'
        gSystem.AddIncludePath(roofitinc)
        print "done"
    else:
        print "failed"
        print 'scram returned:',pscram.returncode,'grep:',pgrep.returncode

print 'end of pyroot_logon'
