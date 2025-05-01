using Microsoft.UI.Xaml;
using WinRT;
using Fang;
using DirectN;
using System.Runtime.InteropServices;

namespace DemoGame;

public sealed partial class MainWindow : Window
{
    private FangEngine? _engine;

    public MainWindow()
    {
        InitializeComponent();
    }

    public void panel_Loaded(object sender, RoutedEventArgs e)
    {
        panel.Loaded -= panel_Loaded;

        var cast = panel.As<ISwapChainPanelNative>();
        _engine = new FangEngine(Marshal.GetIUnknownForObject(cast));
        _engine.Initialize((uint)panel.ActualWidth, (uint)panel.ActualHeight);
    }

    // note: this is *not* the same IID as DirectN.ISwapChainPanelNative which corresponds to the Windows.UI.Xaml.Media namespace
    // this one corresponds to the Microsoft.UI.Xaml.Media namespace
    [ComImport, Guid("63aad0b8-7c24-40ff-85a8-640d944cc325"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public partial interface ISwapChainPanelNative
    {
        [PreserveSig]
        HRESULT SetSwapChain(IDXGISwapChain swapChain);
    }
}
