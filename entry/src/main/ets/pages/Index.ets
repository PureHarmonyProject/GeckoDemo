import gecko from 'libgecko_napi.so';

@Entry
@Component
struct Index {
  @State currentUrl: string = 'https://mozilla.org';
  @State isEngineReady: boolean = false;
  private xComponentController: XComponentController = new XComponentController();

  private onXComponentLoad(context: XComponentContext) {
    // Get native window from XComponent
    const nativeWindow = context.getNativeWindow();

    // Initialize Gecko engine
    this.isEngineReady = gecko.initialize(nativeWindow);

    if (this.isEngineReady) {
      console.info('Gecko engine initialized successfully');
      gecko.loadUrl(this.currentUrl);
    } else {
      console.error('Failed to initialize Gecko engine');
    }
  }

  private onUrlSubmit() {
    if (this.isEngineReady) {
      gecko.loadUrl(this.currentUrl);
    }
  }

  private onGoBack() {
    if (this.isEngineReady) {
      gecko.goBack();
    }
  }

  private onReload() {
    if (this.isEngineReady) {
      gecko.reload();
    }
  }

  build() {
    Column() {
      // Navigation bar
      Row() {
        Button('←').onClick(this.onGoBack)
        Button('↻').onClick(this.onReload)

        TextInput({ text: this.currentUrl })
          .onSubmit(this.onUrlSubmit)
          .layoutWeight(1)
      }
      .height(50)
      .padding(10)

      // Browser content area
      XComponent({
        id: 'gecko_browser',
        type: 'surface',
        controller: this.xComponentController
      })
        .onLoad(this.onXComponentLoad)
        .width('100%')
        .height('100%')
    }
  }
}