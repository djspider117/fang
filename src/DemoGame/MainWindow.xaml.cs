using Microsoft.UI.Xaml;
using Fang;
using System.Runtime.InteropServices;
using System;
using Microsoft.UI.Xaml.Media;

namespace DemoGame;

public sealed partial class MainWindow : Window
{
    public static Guid IID_ISwapChainPanelNative = new("63aad0b8-7c24-40ff-85a8-640d944cc325");

    private FangEngine? _engine;
    private DateTime _lastRender;

    public MainWindow()
    {
        InitializeComponent();
    }

    public unsafe void panel_Loaded(object sender, RoutedEventArgs e)
    {
        panel.Loaded -= panel_Loaded;

        var unk = Marshal.GetIUnknownForObject(panel);
        Marshal.QueryInterface(unk, ref IID_ISwapChainPanelNative, out var interfacePointer);

        _engine = new FangEngine(interfacePointer, @"C:\Work\fang\src\CompiledShaderCache");
        _engine.Initialize((uint)panel.ActualWidth, (uint)panel.ActualHeight);

        CompositionTarget.Rendered += CompositionTarget_Rendered;
    }

    private void CompositionTarget_Rendered(object? sender, RenderedEventArgs e)
    {
        var now = DateTime.Now;

        var deltaTime = now - _lastRender;
        _engine?.Tick(deltaTime.TotalSeconds);
        _lastRender = now;
    }
}
