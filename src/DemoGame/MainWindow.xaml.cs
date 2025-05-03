using Microsoft.UI.Xaml;
using Fang;
using System.Runtime.InteropServices;
using System;
using Microsoft.UI.Xaml.Media;
using System.Threading;
using Microsoft.UI.Xaml.Input;

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
        panel.ManipulationMode = ManipulationModes.TranslateX | ManipulationModes.TranslateY | ManipulationModes.TranslateInertia;
        panel.ManipulationDelta += Panel_ManipulationDelta;
        panel.PreviewKeyDown += Panel_PreviewKeyDown;

        var unk = Marshal.GetIUnknownForObject(panel);
        Marshal.QueryInterface(unk, ref IID_ISwapChainPanelNative, out var interfacePointer);

        _engine = new FangEngine(interfacePointer, @"C:\Work\fang\src\CompiledShaderCache");
        _engine.Initialize((uint)panel.ActualWidth, (uint)panel.ActualHeight);

        SizeChanged += MainWindow_SizeChanged;

        CompositionTarget.Rendering += CompositionTarget_Rendering;
        _lastRender = DateTime.Now;
    }

    private void Panel_PreviewKeyDown(object sender, KeyRoutedEventArgs e)
    {
        if (e.Key == Windows.System.VirtualKey.W)
        {
            var cam = _engine?.GetCameraInterop() ?? throw new InvalidOperationException();

            float forwardX = MathF.Cos(_pitch) * MathF.Sin(_yaw);
            float forwardY = MathF.Sin(_pitch);
            float forwardZ = MathF.Cos(_pitch) * MathF.Cos(_yaw);

            // Apply movement
            _x += forwardX * _moveSpeed * _deltaTime;
            _y += forwardY * _moveSpeed * _deltaTime;
            _z += forwardZ * _moveSpeed * _deltaTime;

            cam.SetPosition(_x, _y, _z);
        }
    }

    private void Panel_ManipulationDelta(object sender, ManipulationDeltaRoutedEventArgs e)
    {
        var cam = _engine?.GetCameraInterop() ?? throw new InvalidOperationException();

        var sensitivity = 20;

        _yaw -= (float)e.Delta.Translation.X / (float)sensitivity;
        _pitch -= (float)e.Delta.Translation.Y / (float)sensitivity;
        _roll += e.Delta.Rotation / (float)sensitivity;

        cam.SetRotations(_yaw * _deltaTime, _pitch * _deltaTime, _roll * _deltaTime);

    }

    private float _x, _y, _z;
    private float _yaw;
    private float _pitch;
    private float _roll;
    private float _moveSpeed = 2.5f;

    private float _deltaTime;

    private void CompositionTarget_Rendering(object? sender, object e)
    {
        var now = DateTime.Now;

        var deltaTime = now - _lastRender;
        _deltaTime = (float)deltaTime.TotalSeconds;
        _engine?.Tick(deltaTime.TotalSeconds);
        _lastRender = now;
    }
}
