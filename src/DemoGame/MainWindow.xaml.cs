using Microsoft.UI.Xaml;
using Fang;
using System.Runtime.InteropServices;
using System;
using Microsoft.UI.Xaml.Media;
using System.Threading;

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

    private void MainWindow_SizeChanged(object sender, WindowSizeChangedEventArgs args)
    {
        _engine?.HandleSizeChanged((uint)args.Size.Width, (uint)args.Size.Height);
    }

    public unsafe void panel_Loaded(object sender, RoutedEventArgs e)
    {
        panel.Loaded -= panel_Loaded;

        var unk = Marshal.GetIUnknownForObject(panel);
        Marshal.QueryInterface(unk, ref IID_ISwapChainPanelNative, out var interfacePointer);

        _engine = new FangEngine(interfacePointer, @"C:\Work\fang\src\CompiledShaderCache");
        _engine.Initialize((uint)panel.ActualWidth, (uint)panel.ActualHeight);

        SizeChanged += MainWindow_SizeChanged;
        //new Thread(RenderThread).Start();

        CompositionTarget.Rendering += CompositionTarget_Rendering;
        //DispatcherTimer timer = new DispatcherTimer();
        //timer.Interval = TimeSpan.FromMicroseconds(16);
        //timer.Tick += Timer_Tick;
        _lastRender = DateTime.Now;
        //timer.Start();
    }

    private void CompositionTarget_Rendering(object? sender, object e)
    {
        var now = DateTime.Now;

        var deltaTime = now - _lastRender;
        _engine?.Tick(deltaTime.TotalSeconds);
        _lastRender = now;
    }

    private void RenderThread(object? obj)
    {
        while (true)
        {
            var now = DateTime.Now;

            var deltaTime = now - _lastRender;
            _engine?.Tick(deltaTime.TotalSeconds);
            _lastRender = now;
        }
    }

    private void Timer_Tick(object? sender, object e)
    {
        var now = DateTime.Now;

        var deltaTime = now - _lastRender;
        _engine?.Tick(deltaTime.TotalSeconds);
        _lastRender = now;
    }

    private void CompositionTarget_Rendered(object? sender, RenderedEventArgs e)
    {
        
    }
}
